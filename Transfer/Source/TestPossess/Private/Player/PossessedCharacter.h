#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player/PlayerCharacter.h"
#include "PossessedCharacter.generated.h"

class UInputDataAsset;
class UPossessComponent;

UCLASS()
class APossessedCharacter : public APlayerCharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere) TObjectPtr<APlayerCharacter> playerCharaRef = nullptr;
	UPROPERTY(EditAnywhere) TSubclassOf<APlayerCharacter> playerCharacterClass = nullptr;
	UPROPERTY(EditAnywhere) TArray<TEnumAsByte<EObjectTypeQuery>> layout = {};


public:
	FORCEINLINE APlayerCharacter* GetPlayerRef() { return playerCharaRef; }

public:
	APossessedCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void LateBinding();
	void Interact();
};