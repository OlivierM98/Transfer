#include "GPE/Pillar.h"
#include "PressurePlate.h"
#include <Kismet/KismetSystemLibrary.h>

APillar::APillar()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	leftPillar = CreateDefaultSubobject<UStaticMeshComponent>("Left");
	centerPillar = CreateDefaultSubobject<UStaticMeshComponent>("Center");
	rightPillar = CreateDefaultSubobject<UStaticMeshComponent>("Right");

	leftPillar->SetupAttachment(RootComponent);
	centerPillar->SetupAttachment(RootComponent);
	rightPillar->SetupAttachment(RootComponent);
}

void APillar::BeginPlay()
{
	Super::BeginPlay();

	leftBasePos = leftPillar->GetComponentLocation();
	centerBasePos = centerPillar->GetComponentLocation();
	rightBasePos = rightPillar->GetComponentLocation();

	FTimerHandle _handle;
	GetWorld()->GetTimerManager().SetTimer(_handle, FTimerDelegate::CreateLambda([&]() {InitMat(); }), 0.03f, false);
}

void APillar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APillar::Activate(APressurePlate* _plate)
{
	if (associations[leftPillar] == _plate)
	{
		leftTargetPos = leftBasePos - FVector(0, 0, offsetVertical);
		ClearTimer(leftHandle);

		GetWorld()->GetTimerManager().SetTimer(leftHandle, FTimerDelegate::CreateLambda([&]() {TogglePath(leftPillar, leftHandle, leftCurrentTime, leftTargetPos); }), 0.01f, true, 0.01f);
	}

	if (associations[centerPillar] == _plate)
	{
		centerTargetPos = centerBasePos - FVector(0, 0, offsetVertical);
		ClearTimer(centerHandle);
		GetWorld()->GetTimerManager().SetTimer(centerHandle, FTimerDelegate::CreateLambda([&]() {TogglePath(centerPillar, centerHandle, centerCurrentTime, centerTargetPos); }), 0.01f, true, 0.01f);
	}

	if (associations[rightPillar] == _plate)
	{
		rightTargetPos = rightBasePos - FVector(0, 0, offsetVertical);
		ClearTimer(rightHandle);
		GetWorld()->GetTimerManager().SetTimer(rightHandle, FTimerDelegate::CreateLambda([&]() {TogglePath(rightPillar, rightHandle, rightCurrentTime, rightTargetPos); }), 0.01f, true, 0.01f);
	}
}

void APillar::Deactivate(APressurePlate* _plate)
{
	if (associations[leftPillar] == _plate)
	{
		leftTargetPos = leftBasePos;
		ClearTimer(leftHandle);
		leftCurrentTime = 0.0f;
		GetWorld()->GetTimerManager().SetTimer(leftHandle, FTimerDelegate::CreateLambda([&]() {TogglePath(leftPillar, leftHandle, leftCurrentTime, leftTargetPos); }), 0.01f, true, 0.01f);
	}

	if (associations[centerPillar] == _plate)
	{
		centerTargetPos = centerBasePos;
		ClearTimer(centerHandle);
		centerCurrentTime = 0.0f;

		GetWorld()->GetTimerManager().SetTimer(centerHandle, FTimerDelegate::CreateLambda([&]() {TogglePath(centerPillar, centerHandle, centerCurrentTime, centerTargetPos); }), 0.01f, true, 0.01f);
	}

	if (associations[rightPillar] == _plate)
	{
		rightTargetPos = rightBasePos;
		ClearTimer(rightHandle);
		rightCurrentTime = 0.0f;
		GetWorld()->GetTimerManager().SetTimer(rightHandle, FTimerDelegate::CreateLambda([&]() {TogglePath(rightPillar, rightHandle, rightCurrentTime, rightTargetPos); }), 0.01f, true, 0.01f);
	}
}

void APillar::InitMat()
{
	if (pressurePlates.Num() <= 0)return;

	int _plateNumber = pressurePlates.Num();

	TArray<UStaticMeshComponent*> _allPillars = { leftPillar, centerPillar, rightPillar };

	int _plateIndex = 0;
	for (int _i = 0; _i < 3; _i++)
	{
		if (_plateIndex >= _plateNumber)
			_plateIndex = 0;

		_allPillars[_i]->SetMaterial(0, pressurePlates[_plateIndex]->GetPlateMaterial());
		associations.Add(_allPillars[_i], pressurePlates[_plateIndex]);

		_plateIndex++;
	}
}

void APillar::TogglePath(UStaticMeshComponent* _pillar, FTimerHandle& _handle, float& _currentTime, FVector& _targetPos)
{
	//UKismetSystemLibrary::PrintString(this, "Y");
	_currentTime += GetWorld()->DeltaTimeSeconds;
	FVector _pos = _pillar->GetComponentLocation();
	FVector _newPos = FMath::Lerp(_pos, _targetPos, _currentTime / animationTime);
	_pillar->SetWorldLocation(_newPos);

	if (_currentTime >= animationTime)
	{
		ClearTimer(_handle);
		_currentTime = 0.0f;
	}
}

void APillar::ClearTimer(FTimerHandle& _handle)
{
	if (_handle.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(_handle);
}