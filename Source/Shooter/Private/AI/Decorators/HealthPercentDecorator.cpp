// First shooter developed by Sevenupi


#include "AI/Decorators/HealthPercentDecorator.h"
#include "AIController.h"
#include "Shooter/Public/Utils.h"
#include "Componets/HealthComponent.h"

UHealthPercentDecorator::UHealthPercentDecorator()
{
	NodeName = "Health Percent";
}

bool UHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return false;

	const auto HealthComponent = UUtils::GetShooterPlayerComponent<UHealthComponent>(Controller->GetPawn());
	if(!HealthComponent || HealthComponent->IsDead()) return false;

	return  HealthComponent->GetHealthPercent() <= HealthPercent;

}
