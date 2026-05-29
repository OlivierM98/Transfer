#include "UI/Menu/MainMenu.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	Init();

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
}

void UMainMenu::Init()
{
	if (playButton)
		playButton->OnClicked.AddDynamic(this, &UMainMenu::Play);

	if (settingButton)
		settingButton->OnClicked.AddDynamic(this, &UMainMenu::Setting);

	if (quitButton)
		quitButton->OnClicked.AddDynamic(this, &UMainMenu::Quit);
}

void UMainMenu::Play()
{
	if (levelToLaunch.IsNull()) return;

	if (levelMusic)
		UGameplayStatics::SpawnSound2D(GetWorld(), levelMusic, 1.0f, 1.0f, 0.0f, nullptr, true, true);

	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), levelToLaunch);
}

void UMainMenu::Setting()
{
	if (!settingsMenuRef)return;

	if (currentSettingsMenu)
	{
		//currentSettingsMenu->RemoveFromViewport();
		currentSettingsMenu->RemoveFromParent();
		currentSettingsMenu = nullptr;
	}

	currentSettingsMenu = CreateWidget<USettingsMenu>(GetWorld(), settingsMenuRef);
	if(currentSettingsMenu)
		currentSettingsMenu->AddToViewport();
}

void UMainMenu::Quit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}