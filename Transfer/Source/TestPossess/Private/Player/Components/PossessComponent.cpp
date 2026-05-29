#include "Player/Components/PossessComponent.h"
#include "PlayerMovementComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Player/PlayerCharacter.h"
#include "Player/Camera/PlayerCameraActor.h"
#include <Player/PossessedCharacter.h>

UPossessComponent::UPossessComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UPossessComponent::BeginPlay()
{
	Super::BeginPlay();

	owner = Cast<APlayerCharacter>(GetOwner());
}

void UPossessComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPossessComponent::TryPossess(const FInputActionValue& _value)
{
	if (APlayerCharacter* _player = Cast<APlayerCharacter>(GetOwner()))
	{
		if (_player->GetMovement()->GetIsMoving())
			return;
	}
	else return;

	FVector _loc = GetOwner()->GetActorLocation();
	FVector _fwd = GetOwner()->GetActorForwardVector();

	float _X = _fwd.X, _Y = _fwd.Y;
	_fwd = FMath::Abs(_X) > FMath::Abs(_Y) ? FVector(_X / FMath::Abs(_X), 0, 0) : FVector(0, _Y / FMath::Abs(_Y), 0);

	FVector _start = _loc + (_fwd * 100);
	_start.Z += 80.0f;
	FVector _end = _loc + (_fwd * 500);
	_end.Z += 80.0f;
	FHitResult _result;
	
	bool _hit = UKismetSystemLibrary::SphereTraceSingle(this, _start, _end,
		radius,
		possessLayout,
		false,
		{},
		useDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		_result,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		1.0f);

	if (!_hit) return;

	APawn* _pawn = Cast<APawn>(_result.GetActor());
	if (_pawn)
	{
		//owner->GetMovement()->ResetDirectionForPossess();

		APlayerController* _controller = GetWorld()->GetFirstPlayerController();
		if (!_controller) return;
		owner->GetCamera()->SetActorToAttach(_pawn);
		_controller->Possess(_pawn);
		_controller->SetViewTargetWithBlend(owner->GetCamera());
	}

}

void UPossessComponent::CancelPossess()
{
	APossessedCharacter* _owner = Cast<APossessedCharacter>(owner);
	if (!_owner) return;
	if (!_owner->GetIsPossessed()) return;

	APawn* _pawn = Cast<APawn>(_owner->GetPlayerRef());
	if (_pawn)
	{
		APlayerController* _controller = GetWorld()->GetFirstPlayerController();
		if (!_controller) return;
		owner->GetCamera()->SetActorToAttach(_pawn);
		_controller->Possess(_pawn);
		_controller->SetViewTargetWithBlend(owner->GetCamera());
	}	
}