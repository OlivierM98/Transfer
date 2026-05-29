#include "Player/BlueCharacter.h"
#include "Player/DataAsset/InputDataAsset.h"
#include <EnhancedInputSubsystems.h>
#include "EnhancedInputComponent.h"
#include "Components/PortalComponent.h"

ABlueCharacter::ABlueCharacter()
{
	portal = CreateDefaultSubobject<UPortalComponent>("Portal");

	AddOwnedComponent(portal);
}

void ABlueCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ABlueCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlueCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UInputDataAsset* _inputDataAsset = GetInputDA();
	if (!_inputDataAsset) return;

	UEnhancedInputComponent* _input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!_input)return;

	_input->BindAction(_inputDataAsset->portalAction, ETriggerEvent::Started, this, &ABlueCharacter::Portal);
}

void ABlueCharacter::Reset()
{
	Super::Reset();

	portal->DestroyPortals();
}

void ABlueCharacter::Portal()
{
	if (!portal) return;
	portal->TryPortal();
}