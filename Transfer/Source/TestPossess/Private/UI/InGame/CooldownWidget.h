#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CooldownWidget.generated.h"

class UProgressBar;

UCLASS()
class UCooldownWidget : public UUserWidget
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCooldownFinished);
	FOnCooldownFinished onCooldownFinished;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UProgressBar> cooldownBar = nullptr;
	UPROPERTY(EditAnywhere) float activeTime = 8.0f;
	UPROPERTY() bool isActive = false;
	UPROPERTY() float currentTime = 0.0f;

public:
	FORCEINLINE FOnCooldownFinished& GetOnCooldownFinished() { return onCooldownFinished; }

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geo, float DeltaTime) override;

public:
	void ActivateCooldown();
	void StopCooldown();

private:
	void UpdateCooldown(float _deltaTime);
};