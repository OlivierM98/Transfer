#include "GPE/ResetLevel.h"
#include <Player/PlayerCharacter.h>
#include <Subsystem/ResetSubsystem.h>

AResetLevel::AResetLevel()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	mesh->SetupAttachment(RootComponent);
}

void AResetLevel::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AResetLevel::ResetLevel);
}

void AResetLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AResetLevel::ResetLevel(AActor* Overlapping, AActor* Overlapped)
{
	if (Cast<APlayerCharacter>(Overlapped))
	{
		FTimerHandle _handle;
		GetWorld()->GetTimerManager().SetTimer(_handle, FTimerDelegate::CreateLambda([&]() {
			GetWorld()->GetGameInstance()->GetSubsystem<UResetSubsystem>()->ResetAll();
			}), 0.1f, false);
	}
}