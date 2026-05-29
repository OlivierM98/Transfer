#include "Player/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include <EnhancedInputSubsystems.h>
#include "EnhancedInputComponent.h"
#include "DataAsset/InputDataAsset.h"
#include "Components/PlayerMovementComponent.h"
#include "Components/PossessComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraActor.h"
#include "PlayerCharacterController.h"
#include <Subsystem/ResetSubsystem.h>

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//Init Camera => Might need to remove replaced with camera actor
	/*springArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	springArm->SetupAttachment(RootComponent);
	camera->SetupAttachment(springArm);*/

	//Init Components
	movement = CreateDefaultSubobject<UPlayerMovementComponent>("Movement");
	possess = CreateDefaultSubobject<UPossessComponent>("Possess");

	AddOwnedComponent(movement);
	AddOwnedComponent(possess);
}

void APlayerCharacter::PossessedBy(AController* _controller)
{
	Super::PossessedBy(_controller);

	/*UKismetSystemLibrary::PrintString(this, FString(GetFName().ToString() + "Possessed"),
		true,
		true,
		FLinearColor::Green,
		25.0f);*/

	isPossessed = true; // A REVOIR Comportement trop bizarre tous appelé aux début puis appelé plusieurs fois en meme tmeps que le unpossessed

	if(skeletalMeshRef && possessedMaterial)
		skeletalMeshRef->SetMaterial(1, possessedMaterial);
}

void APlayerCharacter::UnPossessed() // TODO Need to rework this with event OnPawnPossessChanged => see InGameMainWidget further detail
{
	Super::UnPossessed();

	/*UKismetSystemLibrary::PrintString(this, FString(GetFullName() + "UnPossessed"),
		true,
		true,
		FLinearColor::Red,
		25.0f);*/

	isPossessed = false;

	if (skeletalMeshRef && unpossessedMaterial)
		skeletalMeshRef->SetMaterial(1, unpossessedMaterial);
}

void APlayerCharacter::RegisterReset()
{
	resetLocation = GetActorLocation();
	GetWorld()->GetGameInstance()->GetSubsystem<UResetSubsystem>()->Register(this);
}

void APlayerCharacter::Reset()
{
	movement->StopMovementForTP();
	movement->ResetDirectionForPossess();
	SetActorLocation(resetLocation);
}

UMaterialInterface* APlayerCharacter::GetMaterialForPressurePlate()
{
	if (UMaterialInterface* _mat = GetMesh()->GetMaterial(0))
		return _mat;
	return nullptr;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitIMC();

	cameraActorRef = Cast<APlayerCameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), cameraClass));
	skeletalMeshRef = GetMesh();

	if (skeletalMeshRef && possessedMaterial)
		skeletalMeshRef->SetMaterial(1, possessedMaterial);

	if (IsPlayerControlled() && cameraActorRef)
	{
		APlayerController* _controller = GetWorld()->GetFirstPlayerController();
		_controller->bShowMouseCursor = true;
		_controller->SetViewTargetWithBlend(cameraActorRef);
		cameraActorRef->SetActorToAttach(this);
	}

	RegisterReset();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!inputDataAsset) return;

	UEnhancedInputComponent* _input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!_input)return;

	// ====== Move Inputs =====
	_input->BindAction(inputDataAsset->moveAction, ETriggerEvent::Triggered, movement.Get(), &UPlayerMovementComponent::Movement);

	_input->BindAction(inputDataAsset->moveActionUp, ETriggerEvent::Started, movement.Get(), &UPlayerMovementComponent::UpdateInputUp);
	_input->BindAction(inputDataAsset->moveActionDown, ETriggerEvent::Started, movement.Get(), &UPlayerMovementComponent::UpdateInputDown);
	_input->BindAction(inputDataAsset->moveActionRight, ETriggerEvent::Started, movement.Get(), &UPlayerMovementComponent::UpdateInputRight);
	_input->BindAction(inputDataAsset->moveActionLeft, ETriggerEvent::Started, movement.Get(), &UPlayerMovementComponent::UpdateInputLeft);
	
	_input->BindAction(inputDataAsset->moveActionUp, ETriggerEvent::Completed, movement.Get(), &UPlayerMovementComponent::UpdateInputUp);
	_input->BindAction(inputDataAsset->moveActionDown, ETriggerEvent::Completed, movement.Get(), &UPlayerMovementComponent::UpdateInputDown);
	_input->BindAction(inputDataAsset->moveActionRight, ETriggerEvent::Completed, movement.Get(), &UPlayerMovementComponent::UpdateInputRight);
	_input->BindAction(inputDataAsset->moveActionLeft, ETriggerEvent::Completed, movement.Get(), &UPlayerMovementComponent::UpdateInputLeft);
	// ========================

	_input->BindAction(inputDataAsset->possessAction, ETriggerEvent::Started, possess.Get(), &UPossessComponent::TryPossess);
	_input->BindAction(inputDataAsset->rotateAction, ETriggerEvent::Triggered, movement.Get(), &UPlayerMovementComponent::RotateWithJoystick); //=> Used only with joystick controller
	_input->BindAction(inputDataAsset->mouseAction, ETriggerEvent::Triggered, movement.Get(), &UPlayerMovementComponent::UseKeyboard);
	
	APlayerCharacterController* _controller = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	if(_controller)
		_input->BindAction(inputDataAsset->pauseAction, ETriggerEvent::Started, _controller, &APlayerCharacterController::PauseAction);
}

void APlayerCharacter::InitIMC()
{
	if (!inputDataAsset) return;

	if (ULocalPlayer* _localPlayer = Cast<ULocalPlayer>(GetWorld()->GetFirstLocalPlayerFromController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* _subsystem = _localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			_subsystem->AddMappingContext(inputDataAsset->imc, 0);			
		}
	}
}

void APlayerCharacter::DebugInput()
{
	//UKismetSystemLibrary::PrintString(this, "Input");
}