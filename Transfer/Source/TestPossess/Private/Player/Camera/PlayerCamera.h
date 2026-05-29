#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "PlayerCamera.generated.h"

UCLASS()
class UPlayerCamera : public UCameraComponent
{
	GENERATED_BODY()



public:
	
private:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};