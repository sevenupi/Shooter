// First shooter developed by Sevenupi


#include "Menu/MenuPlayerController.h"


void AMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;

}
