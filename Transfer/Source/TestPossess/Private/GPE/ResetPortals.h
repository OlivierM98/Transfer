#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResetPortals.generated.h"

class APortal;

UCLASS()
class AResetPortals : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh = nullptr;

	UPROPERTY(EditAnywhere) TSubclassOf<APortal> portalClass = nullptr;
	
public:	
	AResetPortals();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION() void Reset(AActor* Overlapped, AActor* Overlapping);
};