#include "UI/InGame/PauseMenu.h"
#include "Components/Button.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if(!initDone)
		InitButton();
}

void UPauseMenu::InitButton()
{
	initDone = true;

	if (resumeButton)
		resumeButton->OnClicked.AddDynamic(this, &UPauseMenu::ResumeAction);

	if (settingsButton)
		settingsButton->OnClicked.AddDynamic(this, &UPauseMenu::SettingsAction);

	if (quitButton)
		quitButton->OnClicked.AddDynamic(this, &UPauseMenu::QuitAction);
}

void UPauseMenu::ResumeAction()
{
	if (currentSettingsMenu && currentSettingsMenu->IsInViewport())
	{
		//currentSettingsMenu->RemoveFromViewport();
		currentSettingsMenu->RemoveFromParent();
		currentSettingsMenu = nullptr;
	}

	//RemoveFromViewport();
	RemoveFromParent();
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UPauseMenu::SettingsAction()
{
	if (!settingsMenuRef)return;

	if (currentSettingsMenu)
	{
		//currentSettingsMenu->RemoveFromViewport();
		currentSettingsMenu->RemoveFromParent();
		currentSettingsMenu = nullptr;
	}

	currentSettingsMenu = CreateWidget<USettingsMenu>(GetWorld(), settingsMenuRef);
	if (currentSettingsMenu)
		currentSettingsMenu->AddToViewport();
}

void UPauseMenu::QuitAction()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
