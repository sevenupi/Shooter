// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

//Only in C++ can be used this event (all names of delegates starts from "F")
DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category="Health")
	bool IsDead() const { return FMath::IsNearlyZero(Health); }

	
	float GetHealth() const {return Health;}

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="Health", meta=(ClampMin = "1.0", ClampMax="1000"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="Health")
	bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="Health", meta=(EditCondition = "AutoHeal", ClampMin = "0.0", ClampMax="100"))
	float HealUpdateTime = 0.3f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="Health", meta=(EditCondition = "AutoHeal",ClampMin = "0.0", ClampMax="100"))
	float HealDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="Health", meta=(EditCondition = "AutoHeal",ClampMin = "0.0", ClampMax="100"))
	float HealModifier = 1.0f;
	
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Health = 0.0f;
	FTimerHandle HealTimerHandle;
	
	UFUNCTION()
	void OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );

	void HealUpdate();
	void SetHealth(float NewHealth);
};