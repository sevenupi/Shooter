// First shooter developed by Sevenupi


#include "AI/Services/FireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Shooter/Public/Utils.h"
#include "Weapon/WeaponComponent.h"

UFireService::UFireService()
{
	NodeName = "Fire";
}

void UFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	
	const auto HasAim = BlackBoard && BlackBoard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if (Controller)
	{
		const auto WeaponComponent = UUtils::GetShooterPlayerComponent<UWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent)
		{
			HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
