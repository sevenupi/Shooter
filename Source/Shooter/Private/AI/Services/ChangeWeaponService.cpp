// First shooter developed by Sevenupi


#include "AI/Services/ChangeWeaponService.h"
#include "Weapon/WeaponComponent.h"
#include "AIController.h"
#include "Shooter/Public/Utils.h"


UChangeWeaponService::UChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void UChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(Controller)
	{
		const auto WeaponComponent = UUtils::GetShooterPlayerComponent<UWeaponComponent>(Controller->GetPawn());
		if(WeaponComponent && Probability > 0 && FMath::FRand()<=Probability)
		{
			WeaponComponent->NextWeapon();
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
