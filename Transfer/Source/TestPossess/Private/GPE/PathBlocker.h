#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathBlocker.generated.h"

UCLASS(abstract)
class APathBlocker : public AActor
{
	GENERATED_BODY()
	
public:	
	APathBlocker();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


public:
	virtual void InitMat(UMaterialInterface* _mat) PURE_VIRTUAL(&APathBlocker::InitMat,);
	virtual void LaunchOpenPath() PURE_VIRTUAL(&APathBlocker::LaunchOpenPath,);
	virtual void LaunchClosePath() PURE_VIRTUAL(&APathBlocker::LaunchClosePath, );

};