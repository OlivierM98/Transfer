#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CloneComponent.generated.h"

class ARedCharacter;
class UCloneSubsystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCloneComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<ARedCharacter> cloneClass = nullptr;

	UPROPERTY(EditAnywhere) float radius = 50.0f;
	UPROPERTY(EditAnywhere) TArray<TEnumAsByte<EObjectTypeQuery>> cloneLayout = {};
	UPROPERTY(EditAnywhere) TEnumAsByte<ETraceTypeQuery> obstacleTrace;

	UPROPERTY() FVector testedLocation = FVector(0);
	UPROPERTY() TObjectPtr<UCloneSubsystem> cloneSubsystem = nullptr;

public:	
	UCloneComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION() void TryCloning();
	UFUNCTION() void DestroyAll();

private:
	void Clone();
	//void RemoveClone(ARedCharacter* _clone);
};