#include "GPE/CheckPoint.h"
#include <Player/PlayerCharacter.h>

ACheckPoint::ACheckPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	
	box = CreateDefaultSubobject<UBoxComponent>("Box");
	box->SetupAttachment(RootComponent);
}

void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
	
	box->OnComponentBeginOverlap.AddDynamic(this, &ACheckPoint::OnOverlapBegin);
}

void ACheckPoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerCharacter* _player = Cast<APlayerCharacter>(OtherActor))
		_player->SetBaseLocation(GetActorLocation());
}