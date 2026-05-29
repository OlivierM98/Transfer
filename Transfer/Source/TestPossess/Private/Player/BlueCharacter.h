#pragma once

#include "CoreMinimal.h"
#include "Player/PossessedCharacter.h"
#include "BlueCharacter.generated.h"

class UPortalComponent;

UCLASS()
class ABlueCharacter : public APossessedCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<UPortalComponent> portal = nullptr;

public:
	ABlueCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Reset() override;
private:
	void Portal();
};