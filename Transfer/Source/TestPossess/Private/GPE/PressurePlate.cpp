#include "GPE/PressurePlate.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Player/PossessedCharacter.h"
#include "Pillar.h"
#include "Player/Components/UsePressurePlateInterface.h"

APressurePlate::APressurePlate()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	plate = CreateDefaultSubobject<UStaticMeshComponent>("Plate");
	base = CreateDefaultSubobject<UStaticMeshComponent>("Base");

	collision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");

	plate->SetupAttachment(RootComponent);
	base->SetupAttachment(RootComponent);

	collision->SetupAttachment(RootComponent);
}

void APressurePlate::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle _handle;
	GetWorld()->GetTimerManager().SetTimer(_handle, FTimerDelegate::CreateLambda([&]() {LateInitialize(); }), 0.01f, false);
}

void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APressurePlate::LateInitialize()
{
	InitMat();
	InitOverlap();
}

void APressurePlate::InitMat()
{
	if (!actorToActivate) return;
	UMaterialInterface* _mat = actorToActivate->GetSkelRef()->GetMaterial(0);

	plate->SetMaterial(0, _mat);
}

void APressurePlate::InitOverlap()
{
	OnActorBeginOverlap.AddDynamic(this, &APressurePlate::VerifyOverlap);
	OnActorEndOverlap.AddDynamic(this, &APressurePlate::StopOverlap);
}

// Overlapped Actor is Himself - OtherActor is the Actor overlapping the pressure plate
void APressurePlate::VerifyOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!actorToActivate) return;

	if (IUsePressurePlateInterface* _actor = Cast<IUsePressurePlateInterface>(OtherActor))
	{
		if (_actor->GetMaterialForPressurePlate() == actorToActivate->GetMaterialForPressurePlate())
		{
			for (int _i = 0; _i < pillars.Num(); _i++)
			{
				if (APillar* _pillar = pillars[_i])
					_pillar->Activate(this);
			}
		}
	}
}

void APressurePlate::StopOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!actorToActivate) return;

	if (IUsePressurePlateInterface* _actor = Cast<IUsePressurePlateInterface>(OtherActor))
	{
		if (_actor->GetMaterialForPressurePlate() == actorToActivate->GetMaterialForPressurePlate())
		{
			for (int _i = 0; _i < pillars.Num(); _i++)
			{
				if (APillar* _pillar = pillars[_i])
					_pillar->Deactivate(this);
			}
		}
	}
}