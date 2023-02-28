// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "Components/ActorComponent.h"
#include "ShooterCoreTypes.h"
#include "WeaponComponent.generated.h"

class ABaseWeapon;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

	virtual void StartFire();
	void StopFire();
	virtual void NextWeapon();
	void Reload();

	bool GetWeaponUIData(FWeaponUIData& UIData) const; 
	bool GetWeaponUIAmmoData(FAmmoData& UIAmmoData) const; 

	bool TryToAddAmmo(TSubclassOf<ABaseWeapon> WeaponType, int32 ClipsAmmount);
	bool NeedAmmo(TSubclassOf<ABaseWeapon> WeaponType);

protected:

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* EquipAnimMontaga;

	UPROPERTY()
	ABaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ABaseWeapon*> Weapons;
	
	// Called when the game starts
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	bool CanFire() const;
	bool CanEquip() const;
	void EquipWeapon(int32 WeaponIndex);
	int32 CurrentWeaponIndex = 0;
private:
	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;


	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;
	
	void SpawnWeapons();
	void AtachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& ScoketName);


	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimation();
	void OnEquipFinished(USkeletalMeshComponent* MeshComp);
	void OnReloadFinished(USkeletalMeshComponent* MeshComp);


	bool CanReload() const;

	void OnEmptyClip(ABaseWeapon* AmmoEmtyWeaponThis);
	void ChangeClip();
	
	
	
};
