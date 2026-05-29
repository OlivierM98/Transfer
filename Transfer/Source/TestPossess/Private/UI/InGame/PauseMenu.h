#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <UI/Menu/SettingsMenu.h>
#include "PauseMenu.generated.h"

class UButton;
class UImage;

UCLASS()
class UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UButton> resumeButton = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UButton> settingsButton = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UButton> quitButton = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UImage> blurredBackground = nullptr;

	UPROPERTY(EditAnywhere) TSubclassOf<USettingsMenu> settingsMenuRef = nullptr;
	UPROPERTY() TObjectPtr<USettingsMenu> currentSettingsMenu = nullptr;

	UPROPERTY() bool initDone = false;

public:
	virtual void NativeConstruct() override;

private:
	void InitButton();

public:
	UFUNCTION() void ResumeAction();

private:
	UFUNCTION() void SettingsAction();
	UFUNCTION() void QuitAction();
};