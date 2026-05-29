#include "Player/RedCharacter.h"
#include "Player/DataAsset/InputDataAsset.h"
#include <EnhancedInputSubsystems.h>
#include "EnhancedInputComponent.h"
#include "Components/CloneComponent.h"

ARedCharacter::ARedCharacter()
{
	clone = CreateDefaultSubobject<UCloneComponent>("Clone");

	AddOwnedComponent(clone);
}

void ARedCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ARedCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARedCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (!clone)return;

	UInputDataAsset* _inputDataAsset = GetInputDA();
	if (!_inputDataAsset) return;

	UEnhancedInputComponent* _input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!_input)return;

	_input->BindAction(_inputDataAsset->portalAction, ETriggerEvent::Started, clone.Get(), &UCloneComponent::TryCloning);
}

void ARedCharacter::Reset()
{
	Super::Reset();

	if (clone)
		clone->DestroyAll();
}