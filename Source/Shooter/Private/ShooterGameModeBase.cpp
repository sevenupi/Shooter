// First shooter developed by Sevenupi


#include "ShooterGameModeBase.h"

#include "GameFramework/HUD.h"
#include "Player/ShooterBaseCharacter.h"
#include "Player/ShooterPlayerController.h"
#include "Ui/GameHUD.h"


AShooterGameModeBase::AShooterGameModeBase()
{
	DefaultPawnClass = AShooterBaseCharacter::StaticClass();
	PlayerControllerClass = AShooterPlayerController::StaticClass();
	HUDClass = AGameHUD::StaticClass();
}

