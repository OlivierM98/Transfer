#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "PlayerCameraActor.generated.h"

class UPlayerCamera;
class USpringArmComponent;

UCLASS()
class APlayerCameraActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<UPlayerCamera> camera = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<USpringArmComponent> springArm = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UCurveFloat> switchCurve = nullptr;

	UPROPERTY() bool needSwitch = false;
	UPROPERTY(VisibleAnywhere) TObjectPtr<AActor> actorToAttach = nullptr;
	UPROPERTY() float currentTime = 0.0f;

public:
	FORCEINLINE void SetActorToAttach(AActor* _toAttach) { actorToAttach = _toAttach; StartSwitch(); }
	
public:	
	APlayerCameraActor();

public:
	void StartSwitch();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION() void LerpSwitch(float _alpha);
	UFUNCTION() void CompleteSwitch();
};