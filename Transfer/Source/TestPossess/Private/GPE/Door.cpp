#include "GPE/Door.h"
#include <Kismet/KismetSystemLibrary.h>

ADoor::ADoor()
{
	door = CreateDefaultSubobject<UStaticMeshComponent>("Door");
	hinge = CreateDefaultSubobject<UStaticMeshComponent>("Hinge");

	hinge->SetupAttachment(RootComponent);
	door->SetupAttachment(hinge);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	baseRot = hinge->GetRelativeRotation();

}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	ClearOpenTimer();
	ClearCloseTimer();
}

void ADoor::InitMat(UMaterialInterface* _mat)
{
	if (!_mat) return;
	door->SetMaterial(0, _mat);
}

void ADoor::LaunchOpenPath()
{
	if (isOpen) return;
	isOpen = true;
	currentTime = 0.0f;
	ClearCloseTimer();
	targetRot = baseRot + FRotator(0, (openToTheRight ? rotation : -rotation), 0);
	GetWorld()->GetTimerManager().SetTimer(openHandle, FTimerDelegate::CreateLambda([&]() {OpenPath(); }), 0.01f, true, 0.01f);
}

void ADoor::LaunchClosePath()
{
	if (!isOpen) return;
	isOpen = false;
	currentTime = 0.0f;
	ClearOpenTimer();
	targetRot = baseRot;
	GetWorld()->GetTimerManager().SetTimer(closeHandle, FTimerDelegate::CreateLambda([&]() {ClosePath(); }), 0.01f, true, 0.01f);
}

void ADoor::OpenPath()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	FRotator _rot = hinge->GetRelativeTransform().GetRotation().Rotator();
	FRotator _newRot = FMath::Lerp(_rot, targetRot, (currentTime / animationTime));
	
	hinge->SetRelativeRotation(_newRot);

	if (currentTime >= animationTime)
	{
		ClearOpenTimer();
		currentTime = 0.0f;
	}
}

void ADoor::ClosePath()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	FRotator _rot = hinge->GetRelativeRotation();
	FRotator _newRot = FMath::Lerp(_rot, targetRot, (currentTime / animationTime));

	hinge->SetRelativeRotation(_newRot);

	if (currentTime >= animationTime)
	{
		ClearCloseTimer();
		currentTime = 0.0f;
	}
}

void ADoor::ClearOpenTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(openHandle);
}

void ADoor::ClearCloseTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(closeHandle);
}