
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

UCLASS()
class APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPause);
	FOnPause onPause;

public:
	FORCEINLINE FOnPause& GetOnPause() { return onPause; }

public:
	UFUNCTION() void PauseAction();
};