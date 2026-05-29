#include "Player/Components/PlayerMovementComponent.h"
#include "Algo/Count.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "Player/PlayerCharacter.h"

UPlayerMovementComponent::UPlayerMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	footSteps = CreateDefaultSubobject<USoundBase>("FootSteps");
}

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	owner = Cast<APlayerCharacter>(GetOwner());
}

void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isMoving)
		LerpMovement();

	if(isKeyboard)
		if(owner->GetIsPossessed())
			OrientsPlayerByMouse(DeltaTime);
}

void UPlayerMovementComponent::Movement(const FInputActionValue& _value)
{
	if (!canMove) return;
	if (!owner)return;


	TArray<bool> _bools = { upInput , downInput , leftInput , rightInput };
	if (Algo::Count(_bools, true) != 1) return;

	FVector _direction = _value.Get<FVector>();

	float _X = _direction.X, _Y = _direction.Y /** -1.0f*/;
	_direction = FMath::Abs(_X) > FMath::Abs(_Y) ? FVector(_X / FMath::Abs(_X), 0, 0) : FVector(0, _Y / FMath::Abs(_Y), 0);

	FVector _detection = detectionDistance * _direction;
	_detection.Z += safetyZDistance;
	start = owner->GetActorLocation();
	_detection += start;

	if (DetectObstacle(start, _detection)) return;

	canMove = false;

	end = (_direction * moveDistance) + start;
	isMoving = true;

	if(footSteps)
		UGameplayStatics::PlaySound2D(GetWorld(), footSteps);
}


void UPlayerMovementComponent::UpdateInputUp(const FInputActionValue& _value)
{
	upInput = _value.Get<bool>();
}

void UPlayerMovementComponent::UpdateInputDown(const FInputActionValue& _value)
{
	downInput = _value.Get<bool>();
}

void UPlayerMovementComponent::UpdateInputRight(const FInputActionValue& _value)
{
	rightInput = _value.Get<bool>();
}

void UPlayerMovementComponent::UpdateInputLeft(const FInputActionValue& _value)
{
	leftInput = _value.Get<bool>();
}

void UPlayerMovementComponent::RotateWithJoystick(const FInputActionValue& _value)
{
	FVector _direction = _value.Get<FVector>();
	if (FVector::Dist2D(_direction, FVector(0)) < 0.05f) return;
	isKeyboard = false;
	float _X = _direction.X, _Y = _direction.Y * -1.0f;
	_direction = FMath::Abs(_X) > FMath::Abs(_Y) ? FVector(_X / FMath::Abs(_X), 0, 0) : FVector(0, _Y / FMath::Abs(_Y), 0);

	FRotator _rot = owner->GetActorRotation();
	FRotator _dir = _direction.Rotation();

	FRotator _newRot = UKismetMathLibrary::RInterpTo(_rot, _dir, GetWorld()->DeltaTimeSeconds, rotationSpeed);
	owner->SetActorRotation(_newRot);
}

void UPlayerMovementComponent::ResetDirectionForPossess()
{
	leftInput = false;
	rightInput = false;
	upInput = false;
	downInput = false;
}

void UPlayerMovementComponent::OrientsPlayerByMouse(float _deltaTime)
{
	// Make the rotation to follow the mouse cursor
	FVector _worldLocation;
	FVector _worldDirection;
	GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(_worldLocation, _worldDirection);

	if (_worldLocation.Length() != 0.00f)
	{
		worldLocation = _worldLocation;
		worldDirection = _worldDirection;
		worldDirection += _worldDirection * 10000.0f;
	}	 

	FHitResult _result;
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), worldLocation, worldLocation + worldDirection,
		mouseOrientationLayout,
		false,
		{},
		EDrawDebugTrace::ForOneFrame,
		_result,
		true);

	FVector _position = owner->GetActorLocation();
	FRotator _lookAt = UKismetMathLibrary::FindLookAtRotation(_position, _result.Location);

	int _yaw = FMath::RoundToDouble(_lookAt.Yaw / 90.0) * 90.0;

	FRotator _rot = owner->GetActorRotation();
	FRotator _newRot = UKismetMathLibrary::RInterpTo(_rot, FRotator(0, _yaw, 0), _deltaTime, rotationSpeed);
	owner->SetActorRotation(FRotator(0, _newRot.Yaw, 0));
}

bool UPlayerMovementComponent::DetectObstacle(FVector _myPos, FVector _detectionPos)
{
	TArray<AActor*> _toIgnores = {owner};

	FHitResult _result;
	bool _hit = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), _myPos, _detectionPos,
		radius,
		obstacleLayout,
		false,
		_toIgnores,
		EDrawDebugTrace::None,
		_result,
		true);
	if(_hit)
		if (APlayerCharacter* _player = Cast<APlayerCharacter>(_result.GetActor()))
			return true;
	return _hit;
}

void UPlayerMovementComponent::LerpMovement()
{
	lerp += GetWorld()->GetDeltaSeconds();
	lerp = lerp >= 1.0f ? 1.0f : lerp;
	FVector _actorPosition = owner->GetActorLocation();
	FVector _position = FMath::Lerp(_actorPosition, end, lerp);
	owner->SetActorRelativeLocation(_position);
	
	if (FVector::Dist(_actorPosition, end) <= 1.0f/movingSmoothness)
	{
		owner->SetActorRelativeLocation(end);
		canMove = true;
		isMoving = false;
		lerp = 0.0f;
	}
}