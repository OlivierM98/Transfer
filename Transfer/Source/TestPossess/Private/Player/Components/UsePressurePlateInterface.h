#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UsePressurePlateInterface.generated.h"

UINTERFACE(MinimalAPI)
class UUsePressurePlateInterface : public UInterface
{
	GENERATED_BODY()
};

class IUsePressurePlateInterface
{
	GENERATED_BODY()

public:
	UFUNCTION() virtual UMaterialInterface* GetMaterialForPressurePlate() = 0;
};