#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class APortal : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh = nullptr;

	UPROPERTY() TObjectPtr<APortal> connectedTo = nullptr;
	
	UPROPERTY(VisibleAnywhere) bool usedTP = false;

	UPROPERTY(EditAnywhere, Category = "Sound") TObjectPtr<USoundBase> portalOverlapSound = nullptr;

public:
	FORCEINLINE UStaticMeshComponent* GetMesh() { return mesh; }

	FORCEINLINE void SetPortalConnected(APortal* _portal) { connectedTo = _portal; }
	FORCEINLINE void PreventInifiniteTP() { usedTP = true; }

public:	
	APortal();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void InitOverlap();
	UFUNCTION() void Overlap(AActor* Overlapped, AActor* Overlapping);
	UFUNCTION() void StopOverlap(AActor* Overlapped, AActor* Overlapping);

};