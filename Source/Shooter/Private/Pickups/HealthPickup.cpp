// First shooter developed by Sevenupi


#include "Pickups/HealthPickup.h"
#include "Componets/HealthComponent.h"
#include "Shooter/Public/Utils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool AHealthPickup::GivePickUpTo(APawn* PlayerPawn)
{
	const auto HelthComponent = UUtils::GetShooterPlayerComponent<UHealthComponent>(PlayerPawn);
	if(!HelthComponent || HelthComponent->IsDead()) return false;
	
	
	UE_LOG(LogHealthPickup, Display, TEXT("Health was picked"));
	return  HelthComponent->TryToAddHealth(HealthAmmount);
}
