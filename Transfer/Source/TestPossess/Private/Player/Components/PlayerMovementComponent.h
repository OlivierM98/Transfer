#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <InputAction.h>
#include "PlayerMovementComponent.generated.h"

class APlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPlayerMovementComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY() TObjectPtr<APlayerCharacter> owner = nullptr;

	// ===== Moving Properties ============
	UPROPERTY(EditAnywhere, Category = "MovingProperties") float moveDistance = 150.0f;
	UPROPERTY(EditAnywhere, Category = "MovingProperties", meta = (UIMin = 0.1f, UIMax = 1000.0f)) float movingSmoothness = 1.0f;
	UPROPERTY(VisibleAnywhere, Category = "MovingProperties") bool canMove = true;
	UPROPERTY(VisibleAnywhere, Category = "MovingProperties") bool isMoving = false;
	UPROPERTY() FVector start;
	UPROPERTY() FVector end;
	UPROPERTY() float lerp = 0.0f;

	// ===== Moving Input Gestion =========
	UPROPERTY() bool upInput = false;
	UPROPERTY() bool downInput = false;
	UPROPERTY() bool rightInput = false;
	UPROPERTY() bool leftInput = false;

	// ===== Obstacle Detection ===========
	UPROPERTY(EditAnywhere, Category = "Detection") float detectionDistance = 150.0f;
	UPROPERTY(EditAnywhere, Category = "Detection") float safetyZDistance = -10.0f;
	UPROPERTY(EditAnywhere, Category = "Detection") float radius = 50.0f;
	UPROPERTY(EditAnywhere, Category = "Detection") TEnumAsByte<ETraceTypeQuery> obstacleLayout;

	// ===== Orientation ==================
	UPROPERTY(EditAnywhere, Category = "Orientation") TEnumAsByte<ETraceTypeQuery> mouseOrientationLayout;
	UPROPERTY(EditAnywhere, Category = "Orientation") float rotationSpeed = 15.0f;
	UPROPERTY() FVector worldLocation = FVector(0);
	UPROPERTY() FVector worldDirection = FVector(0);
	UPROPERTY() bool isKeyboard = true;

	// ===== Sound ========================
	UPROPERTY(EditAnywhere, Category = "Sound") TObjectPtr<USoundBase> footSteps = nullptr;

public:
	FORCEINLINE bool GetIsMoving() { return isMoving; }
	FORCEINLINE void StopMovementForTP() { isMoving = false; canMove = true; lerp = 0.0f; }
	UFUNCTION() void UseKeyboard(const FInputActionValue& _value) { isKeyboard = true; }

public:	
	UPlayerMovementComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// Move the chracter square by square
	UFUNCTION() void Movement(const FInputActionValue& _value);

	// All 4 needed for only have one direction input taken
	UFUNCTION() void UpdateInputUp(const FInputActionValue& _value);
	UFUNCTION() void UpdateInputDown(const FInputActionValue& _value);
	UFUNCTION() void UpdateInputRight(const FInputActionValue& _value);
	UFUNCTION() void UpdateInputLeft(const FInputActionValue& _value);

	UFUNCTION() void RotateWithJoystick(const FInputActionValue& _value);

	UFUNCTION() void ResetDirectionForPossess();

private:
	void OrientsPlayerByMouse(float _deltaTime);
	bool DetectObstacle(FVector _myPos, FVector _detectionPos);
	void LerpMovement();
};