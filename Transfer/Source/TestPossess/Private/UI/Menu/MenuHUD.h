#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.generated.h"

class UMainMenu;

UCLASS()
class AMenuHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<UMainMenu> mainMenuClass = nullptr;
	UPROPERTY() TObjectPtr<UMainMenu> currentMainMenu = nullptr;

public:
	FORCEINLINE UMainMenu* GetMainMenu() { return currentMainMenu; }

private:
	virtual void BeginPlay() override;
	
};
