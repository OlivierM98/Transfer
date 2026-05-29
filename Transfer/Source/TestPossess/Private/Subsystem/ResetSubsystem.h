#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ResetSubsystem.generated.h"

class IResetableInterface;

UCLASS()
class UResetSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY() TArray<TScriptInterface<IResetableInterface>> allResetables = {};

public:
	void Register(TScriptInterface<IResetableInterface> _resetable);
	void ResetAll();
};