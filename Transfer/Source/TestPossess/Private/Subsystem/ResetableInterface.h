#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ResetableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UResetableInterface : public UInterface
{
	GENERATED_BODY()
};

class IResetableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION() virtual void RegisterReset() = 0;
	UFUNCTION() virtual void Reset() = 0;
};