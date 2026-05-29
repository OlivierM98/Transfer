#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameMainWidget.generated.h"

class UCooldownWidget;
class UPauseMenu;
class APlayerCharacter;

UCLASS()
class UInGameMainWidget : public UUserWidget
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStopPossess);
	FOnStopPossess onStopPossess;

	UPROPERTY(EditAnywhere) TSubclassOf<APlayerCharacter> playerClassRef = nullptr;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UCooldownWidget> cooldownWidget = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UPauseMenu> pauseMenu = nullptr;

	UPROPERTY() bool isInPossess = false;

public:
	FORCEINLINE FOnStopPossess& GetOnStopPossess() { return onStopPossess; }

public:
	virtual void NativeConstruct() override;

private:
	void BindToPossessEvent();
	UFUNCTION() void PossessChanged(APawn* _oldPawn, APawn* _newPawn);
	UFUNCTION() void StopPossessWidget();
	void LateInitialize();
	UFUNCTION() void TogglePauseMenu();
};