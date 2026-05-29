#include "GPE/LevelTP.h"
#include <Player/PlayerCharacter.h>
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include <Subsystem/PortalSubsystem.h>

ALevelTP::ALevelTP()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	mesh->SetupAttachment(RootComponent);
}

void ALevelTP::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ALevelTP::NextLevel);
}

void ALevelTP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelTP::NextLevel(AActor* Overlapped, AActor* Overlapping)
{

	if (nextLevel.IsNull()) return;

	if (Cast<APlayerCharacter>(Overlapping))
	{
		GetWorld()->GetGameInstance()->GetSubsystem<UPortalSubsystem>()->DestroyAllPortals();
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), nextLevel);
	}
}