// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponComponent.h"
#include "AIWeaponComponent.generated.h"

UCLASS()
class SHOOTER_API UAIWeaponComponent : public UWeaponComponent
{
	GENERATED_BODY()


public:
	virtual void StartFire() override;
	virtual void NextWeapon() override;
	
};
