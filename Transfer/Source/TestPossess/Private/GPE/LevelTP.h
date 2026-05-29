#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelTP.generated.h"

UCLASS()
class ALevelTP : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh = nullptr;

	UPROPERTY(EditAnywhere) TSoftObjectPtr<UWorld> nextLevel = nullptr;
	
public:	
	ALevelTP();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION() void NextLevel(AActor* Overlapped, AActor* Overlapping);
};