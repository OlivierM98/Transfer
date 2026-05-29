#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "PressurePlate.generated.h"

class APossessedCharacter;
class APillar;

UCLASS()
class APressurePlate : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> plate = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> base = nullptr;

	UPROPERTY(EditAnywhere) TObjectPtr<UBoxComponent> collision = nullptr;

	UPROPERTY(EditAnywhere, Category = "Params") TArray<TObjectPtr<APillar>> pillars = {};
	UPROPERTY(EditAnywhere, Category = "Params") TObjectPtr<APossessedCharacter> actorToActivate = nullptr;
	
public:
	UMaterialInterface* GetPlateMaterial() { return plate->GetMaterial(0); }

public:	
	APressurePlate();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void LateInitialize();
	void InitMat();
	void InitOverlap();
	UFUNCTION() void VerifyOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION() void StopOverlap(AActor* OverlappedActor, AActor* OtherActor);
};