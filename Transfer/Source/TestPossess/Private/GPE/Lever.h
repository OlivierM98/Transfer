#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Subsystem/ResetableInterface.h"
#include <Components/BoxComponent.h>
#include "Lever.generated.h"

class ADoor;
class APossessedCharacter;

UCLASS()
class ALever : public AActor, public IInteractableInterface, public IResetableInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> base = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> bearing = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> handle = nullptr;

	UPROPERTY(EditAnywhere) TObjectPtr<UBoxComponent> box = nullptr;

	UPROPERTY(EditAnywhere) TArray<TObjectPtr<ADoor>> doors = {};
	UPROPERTY(EditAnywhere) TObjectPtr<APossessedCharacter> actorToActivate = nullptr;

	UPROPERTY() bool isActive = false;
	UPROPERTY() float rotationAngle = 90.0f;
	UPROPERTY() float animationTime = 0.15f;
	UPROPERTY() float currentTime = 0.0f;
	UPROPERTY() FTimerHandle toggleHandle;

	UPROPERTY() FRotator baseRot = FRotator();
	UPROPERTY() FRotator actualRot = FRotator();
	UPROPERTY() FRotator targetRot = FRotator();
	
public:	
	ALever();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Interact(AActor* _interactor) override;
	void TryToggle(APossessedCharacter* _actor);

	UFUNCTION() virtual void RegisterReset() override;
	UFUNCTION() virtual void Reset() override;

private:
	void Toggle();
	void InitMat();

};