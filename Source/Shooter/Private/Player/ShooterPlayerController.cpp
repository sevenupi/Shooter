// First shooter developed by Sevenupi


#include "ShooterPlayerController.h"

#include "RespawnComponent.h"

AShooterPlayerController::AShooterPlayerController()
{
	RespawnComponent= CreateDefaultSubobject<URespawnComponent>("RespawnComponent");
}
