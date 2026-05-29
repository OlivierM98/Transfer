#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Subsystem/ResetableInterface.h"
#include "Components/UsePressurePlateInterface.h"
#include "PlayerCharacter.generated.h"

class UInputDataAsset;
class UCameraComponent;
class USpringArmComponent;
class UPlayerMovementComponent;
class UPossessComponent;
class APlayerCameraActor;

UCLASS()
class APlayerCharacter : public ACharacter, public IResetableInterface, public IUsePressurePlateInterface
{
	GENERATED_BODY()	

	//======== Material =================================
	UPROPERTY(EditAnywhere, Category = "Material") TObjectPtr<UMaterialInstance> possessedMaterial = nullptr;
	UPROPERTY(EditAnywhere, Category = "Material") TObjectPtr<UMaterialInstance> unpossessedMaterial = nullptr;

	//======== Input -> Register in a DataAsset =========
	UPROPERTY(EditAnywhere, Category = "Input") TObjectPtr<UInputDataAsset> inputDataAsset = nullptr;

	//======== Camera ===================================
	//UPROPERTY(EditAnywhere, Category = "Camera") TObjectPtr<UCameraComponent> camera = nullptr;
	//UPROPERTY(EditAnywhere, Category = "Camera") TObjectPtr<USpringArmComponent> springArm = nullptr;

	UPROPERTY(EditAnywhere, Category = "Camera") TSubclassOf<APlayerCameraActor> cameraClass = nullptr;
	UPROPERTY(EditAnywhere, Category = "Camera") TObjectPtr<APlayerCameraActor> cameraActorRef = nullptr;

	//======== Components ===============================
	UPROPERTY(EditAnywhere, Category = "Components") TObjectPtr<UPlayerMovementComponent> movement = nullptr;
	UPROPERTY(EditAnywhere, Category = "Components") TObjectPtr<UPossessComponent> possess = nullptr;

	//======== Reset ====================================
	UPROPERTY() FVector resetLocation = FVector(0);

	UPROPERTY()  TObjectPtr<USkeletalMeshComponent> skeletalMeshRef = nullptr;
	UPROPERTY() bool isPossessed = false;

public:
	FORCEINLINE TObjectPtr<UMaterialInstance> GetUnpossessedMat() { return unpossessedMaterial; }
	FORCEINLINE TObjectPtr<USkeletalMeshComponent> GetSkelRef() { return skeletalMeshRef; }
	FORCEINLINE TObjectPtr<APlayerCameraActor> GetCamera() { return cameraActorRef; }
	FORCEINLINE TObjectPtr<UInputDataAsset> GetInputDA() { return inputDataAsset; }
	FORCEINLINE TObjectPtr<UPlayerMovementComponent> GetMovement() { return movement; }
	FORCEINLINE TObjectPtr<UPossessComponent> GetPossess() { return possess; }
	FORCEINLINE bool GetIsPossessed() { return isPossessed; }

	FORCEINLINE void SetIsPossessed(bool _value) { isPossessed = _value; }
	FORCEINLINE void SetBaseLocation(FVector _newLoc) { resetLocation = _newLoc; }

public:
	APlayerCharacter();

	virtual void PossessedBy(AController* _controller) override;
	virtual void UnPossessed() override;
	UFUNCTION() virtual void RegisterReset() override;
	UFUNCTION() virtual void Reset() override;
	UFUNCTION() virtual UMaterialInterface* GetMaterialForPressurePlate() override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	virtual void InitIMC();

	UFUNCTION() void DebugInput();
};