#include "GPE/Portal.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <Player/PlayerCharacter.h>
#include "Player/Components/PlayerMovementComponent.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	mesh->SetupAttachment(RootComponent);

	portalOverlapSound = CreateDefaultSubobject<USoundBase>("PortalOverlapSound");
}

void APortal::BeginPlay()
{
	Super::BeginPlay();
	InitOverlap();
}

void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortal::InitOverlap()
{
	OnActorBeginOverlap.AddDynamic(this, &APortal::Overlap);
	OnActorEndOverlap.AddDynamic(this, &APortal::StopOverlap);
}

// 1 Himself - 2 ActorOverlapping
void APortal::Overlap(AActor* Overlapped, AActor* Overlapping)
{
	if (!connectedTo) return;
	if (usedTP) return;

	connectedTo->PreventInifiniteTP();

	if (APlayerCharacter* _player = Cast<APlayerCharacter>(Overlapping))
		_player->GetMovement()->StopMovementForTP();

	Overlapping->SetActorLocation(connectedTo->GetActorLocation());

	if (portalOverlapSound)
		UGameplayStatics::PlaySound2D(GetWorld(), portalOverlapSound);
}

void APortal::StopOverlap(AActor* Overlapped, AActor* Overlapping)
{
	if (!connectedTo) return;

	usedTP = false;
}