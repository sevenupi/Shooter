// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "HealthPercentDecorator.generated.h"


UCLASS()
class SHOOTER_API UHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UHealthPercentDecorator();

protected:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="AI")
	float HealthPercent =0.6f;
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
