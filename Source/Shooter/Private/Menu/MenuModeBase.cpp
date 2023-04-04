// First shooter developed by Sevenupi


#include "Menu/MenuModeBase.h"
#include "Menu/MenuPlayerController.h"
#include "Menu/UI/MenuHUD.h"

AMenuModeBase::AMenuModeBase()
{
	PlayerControllerClass = AMenuPlayerController::StaticClass();
	HUDClass = AMenuHUD::StaticClass();
}
