#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/UsePressurePlateInterface.h"
#include "Clone.generated.h"

UCLASS()
class AClone : public AActor, public IUsePressurePlateInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<USkeletalMeshComponent> skeletalMesh = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UMaterialInterface> cloneMaterial = nullptr;
	
public:	
	AClone();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION() virtual UMaterialInterface* GetMaterialForPressurePlate() override;
};