// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Weapon/BaseWeapon.h"
#include "LauncherWeapon.generated.h"

class AProjectile;

UCLASS()
class SHOOTER_API ALauncherWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	TSubclassOf<AProjectile> ProjectileClass;
	virtual void MakeShot() override;
	
};
