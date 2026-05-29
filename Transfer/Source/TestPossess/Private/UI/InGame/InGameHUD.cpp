#include "UI/InGame/InGameHUD.h"
#include "InGameMainWidget.h"

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();


	currentMainWidget = CreateWidget<UInGameMainWidget>(GetWorld(), mainWidgetClass);
	if (currentMainWidget)
		currentMainWidget->AddToViewport();
}