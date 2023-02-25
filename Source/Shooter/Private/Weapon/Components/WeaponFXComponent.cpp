// First shooter developed by Sevenupi


#include "Weapon/Components/WeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"

// Sets default values
UWeaponFXComponent::UWeaponFXComponent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto ImpactData = DefaulImpactData;

	if(Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();
		if(ImpactDataMap.Contains(PhysMat))
		{
			ImpactData= ImpactDataMap[PhysMat];
		}
	}

	//first spawn niagara
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),
													ImpactData.NiagaraEffect,
													Hit.ImpactPoint,
													Hit.ImpactNormal.Rotation());

	//second spawn decail
	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),
											ImpactData.DecalData.Material,
											ImpactData.DecalData.Size,
											Hit.ImpactPoint,
											Hit.ImpactNormal.Rotation());
	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
	}
}

