// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EnemyEnvQueryContext.generated.h"


UCLASS()
class SHOOTER_API UEnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
public:
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FName EnemyActorKeyName = "EnemyActor";
};
