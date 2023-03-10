// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterBaseCharacter.generated.h"


class UHealthComponent;
class UWeaponComponent;

UCLASS()
class SHOOTER_API AShooterBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterBaseCharacter(const FObjectInitializer& ObjInit);

protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UHealthComponent* HealthComponent;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UWeaponComponent* WeaponComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	FVector2D LandedDamageVelocity = FVector2D(700.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);
	// Called when the game starts or when spawned

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float LifeSpanOnDeath = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category="Material")
	FName MaterialColorName = "Paint Color";
	
	virtual void BeginPlay() override;
	virtual void OnDeath();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable, Category="Movement")
	virtual bool IsRunning() const;
	
	UFUNCTION(BlueprintCallable, Category="Movement")
	float GetMovementDiraction() const;

	void SetPlayerColor(const FLinearColor& Color);
private:

	void OnHealthChanged(float Health, float HealthDelta);

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
};
