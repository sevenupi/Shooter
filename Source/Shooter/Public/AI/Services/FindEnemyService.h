// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FindEnemyService.generated.h"


UCLASS()
class SHOOTER_API UFindEnemyService : public UBTService
{
	GENERATED_BODY()


public:
	UFindEnemyService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector EnemyActorKey;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
