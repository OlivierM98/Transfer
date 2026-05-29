#include "UI/InGame/InGameMainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PossessedCharacter.h"
#include "CooldownWidget.h"
#include "PauseMenu.h"
#include <Player/PlayerCharacterController.h>

void UInGameMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BindToPossessEvent();
	cooldownWidget->RemoveFromParent();
	pauseMenu->RemoveFromParent();

	FTimerHandle _handle;
	GetWorld()->GetTimerManager().SetTimer(_handle, FTimerDelegate::CreateLambda([&]() {LateInitialize(); }), 0.01f, false);
}

void UInGameMainWidget::BindToPossessEvent()
{
	GetWorld()->GetFirstPlayerController()->OnPossessedPawnChanged.AddDynamic(this, &UInGameMainWidget::PossessChanged);
	cooldownWidget->GetOnCooldownFinished().AddDynamic(this, &UInGameMainWidget::StopPossessWidget);
}

void UInGameMainWidget::PossessChanged(APawn* _oldPawn, APawn* _newPawn)
{
	if (!_newPawn) return;
	//TODO might have a problem at the launch of a level => No problem detected for now
	APossessedCharacter* _possessed = Cast<APossessedCharacter>(_newPawn);
	if (!_possessed) // If it's not a possessedChara then it's the player 
	{
		StopPossessWidget(); // So we stop the widget for possess
		return;
	}

	if (isInPossess) return; // else if we are already in a possess then we keep the current widget active

	isInPossess = true; // else we active the cooldown widget
	cooldownWidget->AddToViewport();
	cooldownWidget->ActivateCooldown();
}

void UInGameMainWidget::StopPossessWidget()
{
	isInPossess = false;
	cooldownWidget->RemoveFromParent();
	cooldownWidget->StopCooldown();
	onStopPossess.Broadcast();
}

void UInGameMainWidget::LateInitialize()
{
	APlayerCharacterController* _controller = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	if (_controller)
		_controller->GetOnPause().AddDynamic(this, &UInGameMainWidget::TogglePauseMenu);
}

void UInGameMainWidget::TogglePauseMenu()
{
	if (pauseMenu->IsInViewport())
	{
		pauseMenu->ResumeAction();
		return;
	}

	pauseMenu->AddToViewport();
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}