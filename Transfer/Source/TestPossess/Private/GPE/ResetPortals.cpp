#include "GPE/ResetPortals.h"
#include <Player/PlayerCharacter.h>
#include "Kismet/GameplayStatics.h"
#include "GPE/Portal.h"

AResetPortals::AResetPortals()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	mesh->SetupAttachment(RootComponent);
}

void AResetPortals::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AResetPortals::Reset);	
}

void AResetPortals::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AResetPortals::Reset(AActor* Overlapped, AActor* Overlapping)
{
	if (!portalClass) return;

	if (Cast<APlayerCharacter>(Overlapping))
	{
		TArray<AActor*> _portals = {};

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), portalClass, _portals);

		for (int _i = 0; _i < _portals.Num(); _i++)
			_portals[_i]->Destroy();
	}
}