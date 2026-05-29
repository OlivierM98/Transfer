#include "UI/Menu/SettingsMenu.h"
#include "Sound/SoundClass.h"

void USettingsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	Init();

	InitSliders();

	/*if (scMusic)
		UpdateMusicVolume(musicVolumeSlider->Value);

	if (scEffect)
		UpdateSoundEffectVolume(effectVolumeSlider->Value);*/
}

void USettingsMenu::Init()
{
	if (effectVolumeSlider)
		effectVolumeSlider->OnValueChanged.AddDynamic(this, &USettingsMenu::UpdateSoundEffectVolume);

	if (musicVolumeSlider)
		musicVolumeSlider->OnValueChanged.AddDynamic(this, &USettingsMenu::UpdateMusicVolume);
	
	if (closeButton)
		closeButton->OnClicked.AddDynamic(this, &USettingsMenu::Close);
}

void USettingsMenu::UpdateSoundEffectVolume(float _value)
{
	if (!scEffect) return;

	scEffect->Properties.Volume = (_value * maxValue) / 100.0f;
	soundEffectValueText->SetText(FText::FromString(FString::FromInt(_value)));
	scEffect->SaveConfig();
}

void USettingsMenu::UpdateMusicVolume(float _value)
{
	if (!scMusic) return;

	scMusic->Properties.Volume = (_value * maxValue) / 100.0f;
	musicValueText->SetText(FText::FromString(FString::FromInt(_value)));
	scMusic->SaveConfig();
}

void USettingsMenu::Close()
{
	//this->RemoveFromViewport();
	this->RemoveFromParent();
}

void USettingsMenu::InitSliders()
{
	if (!scMusic || !scEffect) return;

	int _musicValue = (scMusic->Properties.Volume * 100.0f) / maxValue;
	musicVolumeSlider->SetValue(_musicValue);
	musicValueText->SetText(FText::FromString(FString::FromInt(_musicValue)));

	int _effectValue = (scEffect->Properties.Volume * 100.0f) / maxValue;
	effectVolumeSlider->SetValue(_effectValue);
	soundEffectValueText->SetText(FText::FromString(FString::FromInt(_effectValue)));

}