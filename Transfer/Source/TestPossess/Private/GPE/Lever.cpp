#include "GPE/Lever.h"
#include "Player/PossessedCharacter.h"
#include "GPE/Door.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Subsystem/ResetSubsystem.h>

ALever::ALever()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	box = CreateDefaultSubobject<UBoxComponent>("Box");
	box->SetupAttachment(RootComponent);

	base = CreateDefaultSubobject<UStaticMeshComponent>("Base");
	bearing = CreateDefaultSubobject<UStaticMeshComponent>("Bearing");
	handle = CreateDefaultSubobject<UStaticMeshComponent>("Handle");

	base->SetupAttachment(RootComponent);
	bearing->SetupAttachment(base);
	handle->SetupAttachment(bearing);
}

void ALever::BeginPlay()
{
	Super::BeginPlay();
	
	baseRot = bearing->GetComponentRotation();

	FTimerHandle _handle;
	GetWorld()->GetTimerManager().SetTimer(_handle, FTimerDelegate::CreateLambda([&]() {InitMat(); }), 0.02f, false);
	RegisterReset();
}

void ALever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALever::Interact(AActor* _interactor)
{
	//UKismetSystemLibrary::PrintString(this, "Interact");
	if (APossessedCharacter* _chara = Cast<APossessedCharacter>(_interactor))
		TryToggle(_chara);
}

void ALever::TryToggle(APossessedCharacter* _actor)
{
	if (!_actor) return;

	if (_actor == actorToActivate)
	{
		GetWorld()->GetTimerManager().ClearTimer(toggleHandle);
		actualRot = bearing->GetComponentRotation();
		targetRot = baseRot + (isActive ? FRotator(0) : FRotator(rotationAngle, 0, 0));
		GetWorld()->GetTimerManager().SetTimer(toggleHandle, FTimerDelegate::CreateLambda([&]() {Toggle(); }), 0.01f, true, 0.01f);
	}
}

void ALever::RegisterReset()
{
	GetWorld()->GetGameInstance()->GetSubsystem<UResetSubsystem>()->Register(this);
}

void ALever::Reset()
{
	bearing->SetWorldRotation(baseRot);
	isActive = false;

	int _doorsCount = doors.Num();
	for (int _i = 0; _i < _doorsCount; _i++)
		doors[_i]->LaunchClosePath();
}

void ALever::Toggle()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	FRotator _newRot = FMath::Lerp(actualRot, targetRot, currentTime / animationTime);
	bearing->SetWorldRotation(_newRot);
	if (currentTime >= animationTime)
	{
		GetWorld()->GetTimerManager().ClearTimer(toggleHandle);
		currentTime = 0.0f;
		isActive = !isActive;
		int _doorsCount = doors.Num();
		if (isActive)
			for (int _i = 0; _i < _doorsCount; _i++)
				doors[_i]->LaunchOpenPath();
		else
			for (int _i = 0; _i < _doorsCount; _i++)
				doors[_i]->LaunchClosePath();
	}
}

void ALever::InitMat()
{
	if (!actorToActivate) return;
	UMaterialInterface* _mat = actorToActivate->GetSkelRef()->GetMaterial(0);
	handle->SetMaterial(0, _mat);
	base->SetMaterial(0, _mat);

	if(doors.Num() > 0)
		for (int _i = 0; _i < doors.Num(); _i++)
		{
			doors[_i]->InitMat(_mat);
		}
}