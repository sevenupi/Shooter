// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "LaserWeapon.generated.h"

class UWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class SHOOTER_API ALaserWeapon : public ABaseWeapon
{
	GENERATED_BODY()
	
public:
	ALaserWeapon();
	virtual void StopFire() override;
	virtual void StartFire() override;


	bool TryToAmmoAddHealth(float HealthAmmoAmmount);
	
	bool isAmmohFull() const;
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float TimeBetweenShots = 0.1f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float DamageAmount = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="Weapon")
	bool AutoAmmoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="Weapon", meta=(EditCondition = "AutoAmmoHeal", ClampMin = "0.0", ClampMax="100"))
	float HealAmmoUpdateTime = 0.3f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="Weapon", meta=(EditCondition = "AutoAmmoHeal",ClampMin = "0.0", ClampMax="100"))
	float HealAmmoDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="Weapon", meta=(EditCondition = "AutoAmmoHeal",ClampMin = "0.0", ClampMax="100"))
	float HealAmmoModifier = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	UNiagaraSystem* TraceFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	FString TraceTargetName = "TraceTarget";
	
	UPROPERTY(VisibleAnywhere, Category="VFX")
	UWeaponFXComponent* WeaponFXComponent;
	

	virtual void BeginPlay() override;
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;
private:
	FTimerHandle ShotTimerHandle;
	FTimerHandle HealAmmoTimerHandle;
	
	void MakeDamage(const FHitResult& HitResult);
	void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
	void LasserAmmoUpdate();
};
