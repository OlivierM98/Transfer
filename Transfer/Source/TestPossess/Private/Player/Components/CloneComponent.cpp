#include "Player/Components/CloneComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Player/RedCharacter.h"
#include <Player/PlayerCharacter.h>
#include "PlayerMovementComponent.h"
#include <Subsystem/CloneSubsystem.h>

UCloneComponent::UCloneComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCloneComponent::BeginPlay()
{
	Super::BeginPlay();

	cloneSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCloneSubsystem>();
}

void UCloneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCloneComponent::TryCloning()
{
	if (!cloneSubsystem) return;

	if (APlayerCharacter* _player = Cast<APlayerCharacter>(GetOwner()))
	{
		if (_player->GetMovement()->GetIsMoving())
			return;
	}
	else return;
	
	/*FVector _start = GetOwner()->GetActorLocation();
	testedLocation = GetOwner()->GetActorForwardVector() * 150.0f + _start;*/

	FVector _loc = GetOwner()->GetActorLocation();
	FVector _fwd = GetOwner()->GetActorForwardVector();

	float _X = _fwd.X, _Y = _fwd.Y;
	_fwd = FMath::Abs(_X) > FMath::Abs(_Y) ? FVector(_X / FMath::Abs(_X), 0, 0) : FVector(0, _Y / FMath::Abs(_Y), 0);

	FVector _start = _loc;
	//_start.Z += 80.0f;
	testedLocation = _loc + (_fwd * 150.0f);
	//testedLocation.Z += 80.0f;

	FHitResult _result;

	bool _hit = UKismetSystemLibrary::SphereTraceSingleForObjects(this, _start, testedLocation,
		radius,
		cloneLayout,
		false,
		{},
		EDrawDebugTrace::None,
		_result,
		true);

	if (_hit)
	{
		if (ARedCharacter* _clone = Cast<ARedCharacter>(_result.GetActor()))
			cloneSubsystem->RemoveClone(_clone);
	}
	else
	{
		if (Cast<APlayerCharacter>(GetOwner())->GetMovement()->GetIsMoving()) return;

		bool _hitObstacle = UKismetSystemLibrary::SphereTraceSingle(this, _start, testedLocation,
			radius,
			obstacleTrace,
			false,
			{},
			EDrawDebugTrace::ForDuration,
			_result,
			true);

		if (_hitObstacle) return;
		Clone();
	}
}

void UCloneComponent::DestroyAll()
{
	cloneSubsystem->DestroyAllClones();
}

void UCloneComponent::Clone()
{
	if (!cloneClass) return;
	if (!cloneSubsystem->CanClone()) return;

	ARedCharacter* _clone = GetWorld()->SpawnActor<ARedCharacter>(cloneClass, testedLocation, GetOwner()->GetActorRotation());
	cloneSubsystem->RegisterClone(_clone);
}

//void UCloneComponent::RemoveClone(ARedCharacter* _clone)
//{
//	cloneSubsystem->RemoveClone(_clone);
//}