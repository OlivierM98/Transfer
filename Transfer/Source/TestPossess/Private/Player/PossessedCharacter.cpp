#include "Player/PossessedCharacter.h"
#include "Player/DataAsset/InputDataAsset.h"
#include <EnhancedInputSubsystems.h>
#include "EnhancedInputComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Components/PossessComponent.h"
#include <UI/InGame/InGameHUD.h>
#include "UI/InGame/InGameMainWidget.h"
#include "GPE/InteractableInterface.h"

APossessedCharacter::APossessedCharacter()
{
	PrimaryActorTick.bCanEverTick = true;	
}

void APossessedCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(playerCharacterClass)
		playerCharaRef = Cast<APlayerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), playerCharacterClass));

	SetIsPossessed(false);
	if(UMaterialInstance* _mat = GetUnpossessedMat())
		GetSkelRef()->SetMaterial(1, _mat);

	FTimerHandle _handle;
	GetWorld()->GetTimerManager().SetTimer(_handle, FTimerDelegate::CreateLambda([&]() { LateBinding(); }), 1.0f, false);
}

void APossessedCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APossessedCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UInputDataAsset* _inputDataAsset = GetInputDA();
	if (!_inputDataAsset) return;

	UEnhancedInputComponent* _input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!_input)return;

	_input->BindAction(_inputDataAsset->cancelPossessAction, ETriggerEvent::Triggered, GetPossess().Get(), &UPossessComponent::CancelPossess);
	_input->BindAction(_inputDataAsset->interactAction, ETriggerEvent::Started, this, &APossessedCharacter::Interact);
	//_input->BindAction(_inputDataAsset->portalAction, ETriggerEvent::Triggered, this, &APlayerCharacter::DebugInput);
}

void APossessedCharacter::LateBinding()
{
	if(AHUD* _hud = GetWorld()->GetFirstPlayerController()->GetHUD())
		Cast<AInGameHUD>(_hud)->GetMainWidget()->GetOnStopPossess().AddDynamic(GetPossess().Get(), &UPossessComponent::CancelPossess);
}

void APossessedCharacter::Interact()
{
	FVector _loc = GetActorLocation() + (GetActorForwardVector() * 100.0f);
	FHitResult _result;
	bool _hit = UKismetSystemLibrary::SphereTraceSingleForObjects(this, _loc, _loc,
		75.0f,
		layout,
		false,
		{},
		EDrawDebugTrace::None,
		_result,
		true);

	if (!_hit) return;

	if(IInteractableInterface* _interact = Cast<IInteractableInterface>(_result.GetActor()))
		_interact->Interact(this);
}