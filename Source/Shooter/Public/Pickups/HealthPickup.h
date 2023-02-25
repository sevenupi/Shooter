// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AHealthPickup : public ABasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup", meta=(ClampMin="1.0", ClampMax = "100.0"))
	float HealthAmmount = 40;


private:
	virtual bool GivePickUpTo(APawn* PlayerPawn) override;
};
