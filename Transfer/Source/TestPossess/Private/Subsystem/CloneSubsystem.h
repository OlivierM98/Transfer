#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CloneSubsystem.generated.h"

class ARedCharacter;

UCLASS()
class UCloneSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY() TArray<TObjectPtr<ARedCharacter>> allClones = {};
	UPROPERTY() int maxClones = 3;

public:
	FORCEINLINE bool CanClone() { return allClones.Num() < maxClones; }
	FORCEINLINE int GetCurrentCountClones() { return allClones.Num(); }
	FORCEINLINE int GetMaxClones() { return maxClones; }
	FORCEINLINE UFUNCTION(BlueprintCallable) void SetMaxClones(int _max) { maxClones = _max; }

public:
	void RegisterClone(ARedCharacter* _clone);
	void RemoveClone(ARedCharacter* _clone);
	void DestroyAllClones();
};
