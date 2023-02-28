// First shooter developed by Sevenupi


#include "Weapon/AIWeaponComponent.h"
#include "Weapon/BaseWeapon.h"

void UAIWeaponComponent::StartFire()
{
	if(!CanFire()) return;

	if(CurrentWeapon->IsAmmoEmty())
	{
		NextWeapon();
	}
	else
	{
		CurrentWeapon->StartFire();
	}
}

void UAIWeaponComponent::NextWeapon()
{
	if(!CanFire()) return;

	int32 NextIndex=(CurrentWeaponIndex +1) % Weapons.Num();

	while (NextIndex !=CurrentWeaponIndex)
	{
		if(!Weapons[NextIndex]->IsAmmoEmty()) break;
		NextIndex = (NextIndex+1) % Weapons.Num();
	}

	if(CurrentWeaponIndex != NextIndex)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapon(CurrentWeaponIndex);
	}
}
