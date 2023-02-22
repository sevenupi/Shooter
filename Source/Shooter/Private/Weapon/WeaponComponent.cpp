// First shooter developed by Sevenupi


#include "Weapon/WeaponComponent.h"
#include "Weapon/BaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/EquipFinishedAnimNotify.h"
#include "Animations/ReloadFinishedAnimNotify.h"
#include "Animations/AnimUtils.h"


DEFINE_LOG_CATEGORY_STATIC (LogWeaponComponent, All, All);
// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UWeaponComponent::StartFire()
{
	if(!CanFire()) return;
	CurrentWeapon->StartFire();
}
void UWeaponComponent::StopFire()
{
	if(!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void UWeaponComponent::NextWeapon()
{
	if(!CanEquip()) return;
	
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::Reload()
{
	ChangeClip();
}

bool UWeaponComponent::GetWeaponUIData(FWeaponUIData& UIData) const
{
	if(CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIData();
		return true;
	}
	return false;
}

bool UWeaponComponent::GetWeaponUIAmmoData(FAmmoData& UIAmmoData) const
{
	if(CurrentWeapon)
	{
		UIAmmoData = CurrentWeapon->GetCurrentAmmoData();
		return true;
	}
	return false;
}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentWeaponIndex = 0;
	InitAnimation();
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for(auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
	Super::EndPlay(EndPlayReason);
}

void UWeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!GetWorld() || !Character) return;
	
	for (auto OneWeaponData : WeaponData)
	{
		auto Weapon = GetWorld()->SpawnActor<ABaseWeapon>(OneWeaponData.WeaponClass);
		if(!Weapon) continue;

		Weapon->OnclipEmty.AddUObject(this, &UWeaponComponent::OnEmptyClip);// подпись на делегат 
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AtachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
	
}

void UWeaponComponent::AtachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent,
	const FName& ScoketName)
{
	if (!Weapon || !SceneComponent) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, ScoketName);
	
}

void UWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if(WeaponIndex<0 || WeaponIndex>= Weapons.Num())
	{
		UE_LOG(LogWeaponComponent, Warning, TEXT("Invalid weapon index"));
		return;
	}
	
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;
	
	if(CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AtachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}
	CurrentWeapon = Weapons[WeaponIndex];

	//	if(WeaponData[WeaponIndex].HasReload)
	{
		const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data)
		{
			return Data.WeaponClass == CurrentWeapon->GetClass();
		});
		CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr; 
		//CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
	}
	AtachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	EquipAnimInProgress = true;
	PlayAnimMontage(EquipAnimMontaga);
}

void UWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;

	Character->PlayAnimMontage(Animation);
}

void UWeaponComponent::InitAnimation()
{
	auto EquipFinishedNotifie = AnimUtils::FindNotifyByClass<UEquipFinishedAnimNotify>(EquipAnimMontaga);
	if(EquipFinishedNotifie)
	{
		EquipFinishedNotifie->OnNotified.AddUObject(this, &UWeaponComponent::OnEquipFinished);
	}
	else
	{
		UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify is forgoten to set"));
	}

	for(auto OneWeaponData : WeaponData)
	{
		auto ReloadFinishedNotifie = AnimUtils::FindNotifyByClass<UReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
		if(!ReloadFinishedNotifie)
		{
			UE_LOG(LogWeaponComponent, Error, TEXT("Reload anim notify is forgoten to set"));
		}
		
			ReloadFinishedNotifie->OnNotified.AddUObject(this, &UWeaponComponent::OnReloadFinished);
		
	}
}

void UWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character ||MeshComp != Character->GetMesh()) return;
	
	EquipAnimInProgress = false;
	UE_LOG(LogWeaponComponent, Display, TEXT("Equip finished ") );
}

void UWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character ||MeshComp != Character->GetMesh()) return;
	
	ReloadAnimInProgress = false;
	UE_LOG(LogWeaponComponent, Display, TEXT("Reload finished ") );
}

bool UWeaponComponent::CanFire() const
{
	return CurrentWeapon
			&& !EquipAnimInProgress
			&& !ReloadAnimInProgress;
}

bool UWeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress
			&& !ReloadAnimInProgress;
}

bool UWeaponComponent::CanReload() const
{
	return CurrentWeapon
			&& !EquipAnimInProgress
			&& !ReloadAnimInProgress
			&& CurrentWeapon->CanReload();
}

void UWeaponComponent::OnEmptyClip()
{
	ChangeClip();
}

void UWeaponComponent::ChangeClip()
{
	if(!CanReload()) return;
	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	ReloadAnimInProgress = true;
	PlayAnimMontage((CurrentReloadAnimMontage));
}




