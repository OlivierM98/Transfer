#pragma once

#include "CoreMinimal.h"
#include "GPE/PathBlocker.h"
#include "Door.generated.h"

UCLASS()
class ADoor : public APathBlocker
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> door = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> hinge = nullptr;

	UPROPERTY(EditAnywhere) bool openToTheRight = true;
	UPROPERTY() bool isOpen = false;
	UPROPERTY() float rotation = 90.0f;
	UPROPERTY() float currentTime = 0.0f;
	UPROPERTY() FRotator targetRot = FRotator(0);
	UPROPERTY() FRotator baseRot = FRotator(0);

	UPROPERTY() FTimerHandle openHandle;
	UPROPERTY() FTimerHandle closeHandle;
	UPROPERTY() float animationTime = 0.50f;
	
public:
	ADoor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void InitMat(UMaterialInterface* _mat) override;
	virtual void LaunchOpenPath() override;
	virtual void LaunchClosePath() override;

private:
	void OpenPath();
	void ClosePath();
	void ClearOpenTimer();
	void ClearCloseTimer();
};