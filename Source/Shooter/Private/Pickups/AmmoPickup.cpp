// First shooter developed by Sevenupi


#include "Pickups/AmmoPickup.h"
#include "Componets/HealthComponent.h"
#include "Weapon/WeaponComponent.h"
#include "Shooter/Public/Utils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool AAmmoPickup::GivePickUpTo(APawn* PlayerPawn)
{
	const auto HelthComponent = UUtils::GetShooterPlayerComponent<UHealthComponent>(PlayerPawn);
	if(!HelthComponent || HelthComponent->IsDead()) return false;

	const auto WeaponComponent = UUtils::GetShooterPlayerComponent<UWeaponComponent>(PlayerPawn);
	if(!WeaponComponent) return false;
	
	UE_LOG(LogAmmoPickup, Display, TEXT("Ammo was picked"));
	return  WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmmount);
}
