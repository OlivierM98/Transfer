#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResetLevel.generated.h"

UCLASS()
class AResetLevel : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	
public:	
	AResetLevel();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION() void ResetLevel(AActor* Overlapping, AActor* Overlapped);
};