// First shooter developed by Sevenupi


#include "AI/EQS/FindAmmoDecorator.h"
#include "AIController.h"
#include "Shooter/Public/Utils.h"
#include "Weapon/WeaponComponent.h"

UFindAmmoDecorator::UFindAmmoDecorator()
{
	NodeName ="Need Ammo";
}

bool UFindAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return false;

	const auto WeaponComponent = UUtils::GetShooterPlayerComponent<UWeaponComponent>(Controller->GetPawn());
	if(!WeaponComponent ) return false;

	
	return  WeaponComponent->NeedAmmo(WeaponType);
}
