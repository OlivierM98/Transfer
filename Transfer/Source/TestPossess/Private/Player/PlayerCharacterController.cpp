#include "Player/PlayerCharacterController.h"

void APlayerCharacterController::PauseAction()
{
	onPause.Broadcast();
}