#include "Player/Clone.h"

AClone::AClone()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	skeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Skeleton");
	skeletalMesh->SetupAttachment(RootComponent);
}

void AClone::BeginPlay()
{
	Super::BeginPlay();
	
	if(cloneMaterial && skeletalMesh)
		skeletalMesh->SetMaterial(0, cloneMaterial);

	//SetActorLocation
}

void AClone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UMaterialInterface* AClone::GetMaterialForPressurePlate()
{
	if (UMaterialInterface* _mat = skeletalMesh->GetMaterial(0))
		return _mat;
	return nullptr;
}