#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "SettingsMenu.h"
#include "MainMenu.generated.h"

UCLASS()
class UMainMenu : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UButton> playButton = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UButton> settingButton = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UButton> quitButton = nullptr;

	UPROPERTY(EditAnywhere) TSoftObjectPtr<UWorld> levelToLaunch = nullptr;

	UPROPERTY(EditAnywhere) TObjectPtr<USoundBase> levelMusic = nullptr;

	UPROPERTY(EditAnywhere) TSubclassOf<USettingsMenu> settingsMenuRef = nullptr;
	UPROPERTY() TObjectPtr<USettingsMenu> currentSettingsMenu = nullptr;

public:
	virtual void NativeConstruct() override;

private:
	void Init();
	UFUNCTION() void Play();
	UFUNCTION() void Setting();
	UFUNCTION() void Quit();
};