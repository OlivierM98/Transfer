#include "UI/Menu/MenuHUD.h"
#include "MainMenu.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	currentMainMenu = CreateWidget<UMainMenu>(GetWorld(), mainMenuClass);
	if (currentMainMenu)
		currentMainMenu->AddToViewport();
}