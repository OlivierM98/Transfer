#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PortalComponent.generated.h"

class APortal;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPortalComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<APortal> portalClassRef = nullptr;
	//UPROPERTY(EditAnywhere) TObjectPtr<APortal> firstPortal = nullptr;
	//UPROPERTY(EditAnywhere) TObjectPtr<APortal> secondPortal = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UMaterialInterface> secondPortalMaterial = nullptr;

	UPROPERTY(EditAnywhere) TEnumAsByte<ETraceTypeQuery> portalTrace;

	UPROPERTY(EditAnywhere, Category = "Sound") TObjectPtr<USoundBase> portalCreationSound = nullptr;

	UPROPERTY() bool canPortal = true;
	UPROPERTY() bool flipFlop = true;

	UPROPERTY() float radius = 50.0f;
	UPROPERTY() FVector testedLoc = FVector(0);

public:	
	UPortalComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void TryPortal();
	void DestroyPortals();

private:
	void CreatePortal();
	void FirstPortal();
	void SecondPortal();
};