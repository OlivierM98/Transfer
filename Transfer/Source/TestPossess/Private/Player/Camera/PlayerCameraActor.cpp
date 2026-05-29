#include "Player/Camera/PlayerCameraActor.h"
#include "PlayerCamera.h"
#include <GameFramework/SpringArmComponent.h>
#include <Kismet/KismetSystemLibrary.h>

APlayerCameraActor::APlayerCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	springArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	camera = CreateDefaultSubobject<UPlayerCamera>("Camera");

	springArm->SetupAttachment(RootComponent);
	camera->SetupAttachment(springArm);
}

void APlayerCameraActor::StartSwitch()
{
	//UKismetSystemLibrary::PrintString(this, "Switch Started");

}

void APlayerCameraActor::BeginPlay()
{
	Super::BeginPlay();

	//UKismetSystemLibrary::PrintString(this, "Camera BeginPLay");

	CompleteSwitch();
}

void APlayerCameraActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

void APlayerCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!actorToAttach) return;
	currentTime += DeltaTime;
	LerpSwitch(switchCurve->GetFloatValue(currentTime));
}

void APlayerCameraActor::LerpSwitch(float _alpha)
{
	if (!actorToAttach) return;
	//UKismetSystemLibrary::PrintString(this, "Camera Lerp");

	FVector _lerp = FMath::Lerp(GetActorLocation(), actorToAttach->GetActorLocation(), _alpha);
	SetActorLocation(_lerp);

	if (_alpha >= 1.0f)
		CompleteSwitch();
}

void APlayerCameraActor::CompleteSwitch()
{
	if (!actorToAttach) return;

	FAttachmentTransformRules _rules = FAttachmentTransformRules::KeepWorldTransform;

	AttachToActor(actorToAttach, _rules);
	actorToAttach = nullptr;
	currentTime = 0.0f;
	//UKismetSystemLibrary::PrintString(this, "AAttach Done");
}