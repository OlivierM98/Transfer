#include "GPE/PathBlocker.h"

APathBlocker::APathBlocker()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

}

void APathBlocker::BeginPlay()
{
	Super::BeginPlay();
	
}

void APathBlocker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}