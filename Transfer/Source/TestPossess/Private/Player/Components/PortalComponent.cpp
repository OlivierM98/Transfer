#include "Player/Components/PortalComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "GPE/Portal.h"
#include <Subsystem/PortalSubsystem.h>
#include <Player/PlayerCharacter.h>
#include "Player/Components/PlayerMovementComponent.h"

UPortalComponent::UPortalComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	portalCreationSound = CreateDefaultSubobject<USoundBase>("PortalCreationSound");
}

void UPortalComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UPortalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPortalComponent::TryPortal()
{
	if (APlayerCharacter* _player = Cast<APlayerCharacter>(GetOwner()))
	{
		if (_player->GetMovement()->GetIsMoving())
			return;
	}
	else return;

	TArray<FHitResult> _results;

	/*FVector _start = GetOwner()->GetActorLocation();
	testedLoc = GetOwner()->GetActorForwardVector() * 150.0f + _start;*/

	FVector _loc = GetOwner()->GetActorLocation();
	FVector _fwd = GetOwner()->GetActorForwardVector();

	float _X = _fwd.X, _Y = _fwd.Y;
	_fwd = FMath::Abs(_X) > FMath::Abs(_Y) ? FVector(_X / FMath::Abs(_X), 0, 0) : FVector(0, _Y / FMath::Abs(_Y), 0);

	FVector _start = _loc;
	testedLoc = _loc + (_fwd * 150.0f);

	bool _hit = UKismetSystemLibrary::SphereTraceMulti(this, testedLoc, testedLoc,
		radius,
		portalTrace,
		false,
		{},
		EDrawDebugTrace::None,
		_results,
		true);

	if (_hit) return;
	//if (!canPortal) return;

	CreatePortal();
}

void UPortalComponent::DestroyPortals()
{
	GetWorld()->GetGameInstance()->GetSubsystem<UPortalSubsystem>()->DestroyAllPortals();

	/*if (firstPortal)
		firstPortal->Destroy();
	if (secondPortal)
		secondPortal->Destroy();*/
}

void UPortalComponent::CreatePortal()
{
	if (!portalClassRef) return;

	if (GetWorld()->GetGameInstance()->GetSubsystem<UPortalSubsystem>()->GetFlipFlop())
		FirstPortal();
	else
		SecondPortal();

	if (portalCreationSound)
		UGameplayStatics::PlaySound2D(GetWorld(), portalCreationSound);
}

void UPortalComponent::FirstPortal()
{
	/*if (firstPortal)
		firstPortal->Destroy();*/
	APortal* _portal = GetWorld()->SpawnActor<APortal>(portalClassRef, testedLoc, FRotator(0));
	GetWorld()->GetGameInstance()->GetSubsystem<UPortalSubsystem>()->AddPortal(_portal);

	/*if (secondPortal)
	{
		firstPortal->SetPortalConnected(secondPortal);
		secondPortal->SetPortalConnected(firstPortal);
	}*/
}

void UPortalComponent::SecondPortal()
{
	/*if (secondPortal)
		secondPortal->Destroy();*/

	APortal* _portal = GetWorld()->SpawnActor<APortal>(portalClassRef, testedLoc, FRotator(0));
	_portal->GetMesh()->SetMaterial(0, secondPortalMaterial);

	GetWorld()->GetGameInstance()->GetSubsystem<UPortalSubsystem>()->AddPortal(_portal);
	/*if (firstPortal)
	{
		secondPortal->SetPortalConnected(firstPortal);
		firstPortal->SetPortalConnected(secondPortal);
	}*/
}
