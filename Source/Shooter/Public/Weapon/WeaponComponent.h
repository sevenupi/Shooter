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

	void StartFire();
	void StopFire();
	void NextWeapon();
	void Reload();

	bool GetWeaponUIData(FWeaponUIData& UIData) const; 
	bool GetWeaponUIAmmoData(FAmmoData& UIAmmoData) const; 

	bool TryToAddAmmo(TSubclassOf<ABaseWeapon> WeaponType, int32 ClipsAmmount);

protected:

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* EquipAnimMontaga;
	
	// Called when the game starts
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	UPROPERTY()
	ABaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ABaseWeapon*> Weapons;

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	int32 CurrentWeaponIndex = 0;
	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;
	
	void SpawnWeapons();
	void AtachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& ScoketName);
	void EquipWeapon(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimation();
	void OnEquipFinished(USkeletalMeshComponent* MeshComp);
	void OnReloadFinished(USkeletalMeshComponent* MeshComp);

	bool CanFire() const;
	bool CanEquip() const;
	bool CanReload() const;

	void OnEmptyClip(ABaseWeapon* AmmoEmtyWeaponThis);
	void ChangeClip();
	
	
	
};
