#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputDataAsset.generated.h"

/**
 * Create a data asset to keep all the input information for the player character
 * So if the BP_PlayerCharacter break it's simple to put it back
 */

class UInputMappingContext;
class UInputAction;

UCLASS()
class UInputDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere) TObjectPtr<UInputMappingContext> imc = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> moveAction = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> moveActionUp = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> moveActionDown = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> moveActionRight = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> moveActionLeft = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> rotateAction = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> interactAction = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> possessAction = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> cancelPossessAction = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> portalAction = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> pauseAction = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> mouseAction = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> joystickAction = nullptr;
	
};