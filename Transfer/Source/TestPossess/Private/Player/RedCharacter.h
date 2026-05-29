#pragma once

#include "CoreMinimal.h"
#include "Player/PossessedCharacter.h"
#include "RedCharacter.generated.h"

class UCloneComponent;

UCLASS()
class ARedCharacter : public APossessedCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<UCloneComponent> clone = nullptr;
	
public:
	ARedCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Reset() override;
};
