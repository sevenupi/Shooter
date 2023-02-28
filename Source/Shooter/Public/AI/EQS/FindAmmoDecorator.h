// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "FindAmmoDecorator.generated.h"

class ABaseWeapon;

UCLASS()
class SHOOTER_API UFindAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
	UFindAmmoDecorator();

protected:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="AI")
	TSubclassOf<ABaseWeapon> WeaponType;;
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
