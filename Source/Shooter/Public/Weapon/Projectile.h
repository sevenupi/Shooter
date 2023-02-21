// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
UCLASS()
class SHOOTER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	AProjectile();

	void SetShotDirection(const FVector& Direction){ ShotDirection = Direction;}
protected:

	UPROPERTY(VisibleAnywhere, Category="Weapon")
	USphereComponent* CollisionComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Weapon")
	float SphereRadius = 5.0f;
	
	UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
	UProjectileMovementComponent* MovementComponent;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Weapon")
	float DamageRadius = 200.0f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Weapon")
	float DamageAmount = 50.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Weapon")
	bool DoFullDamage = false;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Weapon")
	float LifeSeconds = 5.0f;
	
	virtual void BeginPlay() override;

private:
	FVector ShotDirection;

	UFUNCTION()
	void OnProjectileHit (UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	AController* GetController() const;
};
