#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PortalSubsystem.generated.h"

class APortal;

UCLASS()
class UPortalSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY() TArray<TObjectPtr<APortal>> portals = {};
	UPROPERTY() bool flipFlop = true;

public:
	TArray<TObjectPtr<APortal>> GetPortals() { return portals; }
	int GetFlipFlop() { return flipFlop; }

public:
	void AddPortal(APortal* _portal);
	void DestroyAllPortals();
};
