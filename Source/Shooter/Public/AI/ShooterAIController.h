// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"


class UShooterAIPerceptionComponent;
class URespawnComponent;

UCLASS()
class SHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

public:
	AShooterAIController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UShooterAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	URespawnComponent* RespawnComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FName FocusOnKeyName ="EnemyActor";
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual  void Tick(float DeltaSeconds) override;

private:
	AActor* GetFocusOnActor() const;
};
