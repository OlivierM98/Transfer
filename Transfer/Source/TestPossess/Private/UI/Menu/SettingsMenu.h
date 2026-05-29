#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Slider.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "SettingsMenu.generated.h"

UCLASS()
class USettingsMenu : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UButton> closeButton = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<USlider> effectVolumeSlider = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<USlider> musicVolumeSlider = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UTextBlock> soundEffectValueText = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UTextBlock> musicValueText = nullptr;

	UPROPERTY(EditAnywhere, Category = "Sound Class") TObjectPtr<USoundClass> scMusic = nullptr;
	UPROPERTY(EditAnywhere, Category = "Sound Class") TObjectPtr<USoundClass> scEffect = nullptr;

	UPROPERTY() float maxValue = 2.0f;

public:
	virtual void NativeConstruct() override;

private:
	void Init();

	UFUNCTION() void UpdateSoundEffectVolume(float _value);
	UFUNCTION() void UpdateMusicVolume(float _value);
	UFUNCTION() void Close();

	void InitSliders();
};