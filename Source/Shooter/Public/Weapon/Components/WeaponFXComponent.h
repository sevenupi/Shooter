// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShooterCoreTypes.h"
#include "WeaponFXComponent.generated.h"


class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTER_API UWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	UWeaponFXComponent();


	void PlayImpactFX(const FHitResult& Hit);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	FImpactData DefaulImpactData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap; // Структура данных, Ассоциативный контейнер который хранит данные ключа и значения, ланный контейнер дженерик
};
