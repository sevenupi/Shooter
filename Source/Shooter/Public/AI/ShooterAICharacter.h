// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "Player/ShooterBaseCharacter.h"
#include "ShooterAICharacter.generated.h"



class UBehaviorTree;
UCLASS()
class SHOOTER_API AShooterAICharacter : public AShooterBaseCharacter
{
	GENERATED_BODY()

public:
	AShooterAICharacter(const FObjectInitializer& objInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
	UBehaviorTree* BehaviorTreeAsset;

protected:
	virtual void OnDeath() override;
};
