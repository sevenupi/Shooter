#pragma once

#include "ShooterCoreTypes.generated.h"

//weaponBase
class ABaseWeapon;
DECLARE_MULTICAST_DELEGATE(FonClipEmtySignature)
USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	int32 Bullets;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon", meta = (EditCondition ="!Infinite"))
	int32 CLips;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	bool Infinite;
};

//WeaponComponent
USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	TSubclassOf<ABaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	UAnimMontage* ReloadAnimMontage;
};

//health component
//Only in C++ can be used this event (all names of delegates starts from "F")
DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);