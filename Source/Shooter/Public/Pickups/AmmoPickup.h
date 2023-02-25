// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "AmmoPickup.generated.h"

class ABaseWeapon;
UCLASS()
class SHOOTER_API AAmmoPickup : public ABasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup", meta=(ClampMin="1.0", ClampMax = "10.0"))
	int32 ClipsAmmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
	TSubclassOf<ABaseWeapon> WeaponType;
private:
	virtual bool GivePickUpTo(APawn* PlayerPawn) override;	
};
