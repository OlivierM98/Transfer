#pragma once

#include "CoreMinimal.h"
#include "GPE/PathBlocker.h"
#include "Pillar.generated.h"

class APressurePlate;

UCLASS()
class APillar : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> leftPillar = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> centerPillar = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> rightPillar = nullptr;
	
	UPROPERTY(EditAnywhere) TArray<TObjectPtr<APressurePlate>> pressurePlates = {};
	
	// Map used to associate pillar with pressure plate enabling multiple same color pressure plate to activate different part of the pillars
	UPROPERTY() TMap<TObjectPtr<UStaticMeshComponent>, TObjectPtr<APressurePlate>> associations = {};

	UPROPERTY(EditAnywhere)	float animationTime = 0.50f;
	UPROPERTY()	float offsetVertical = 150.0f;

	UPROPERTY()	float leftCurrentTime = 0.0f;
	UPROPERTY()	float centerCurrentTime = 0.0f;
	UPROPERTY()	float rightCurrentTime = 0.0f;

	UPROPERTY() FVector leftBasePos = FVector(0);
	UPROPERTY() FVector centerBasePos = FVector(0);
	UPROPERTY() FVector rightBasePos = FVector(0);

	UPROPERTY() FVector leftTargetPos = FVector(0);
	UPROPERTY() FVector centerTargetPos = FVector(0);
	UPROPERTY() FVector rightTargetPos = FVector(0);

	UPROPERTY() FTimerHandle leftHandle;
	UPROPERTY() FTimerHandle centerHandle;
	UPROPERTY() FTimerHandle rightHandle;

public:
	APillar();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


public:
	void Activate(APressurePlate* _plate);
	void Deactivate(APressurePlate* _plate);

private:
	void InitMat();
	UFUNCTION() void TogglePath(UStaticMeshComponent* _pillar, FTimerHandle& _handle, float& _currentTime, FVector& _targetPos);
	void ClearTimer(FTimerHandle& _handle);
};