// First shooter developed by Sevenupi


#include "UI/SpectatorWidget.h"
#include "Shooter/Public/Utils.h"
#include "Componets/RespawnComponent.h"

bool USpectatorWidget::GetRespawnTime(int32& CountDownTime)
{
	const auto RespawnComponent = UUtils::GetShooterPlayerComponent<URespawnComponent>(GetOwningPlayer());
	if(!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

	CountDownTime = RespawnComponent->GetRespawnCountDawn();
	return true;
}
