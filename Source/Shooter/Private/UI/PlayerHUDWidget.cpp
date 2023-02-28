// First shooter developed by Sevenupi


#include "UI/PlayerHUDWidget.h"
#include "Componets/HealthComponent.h"
#include "Weapon/WeaponComponent.h"
#include "Weapon/BaseWeapon.h"
#include "Shooter/Public/Utils.h"

float UPlayerHUDWidget::Get_HealthPercent() const
{
	const auto HealthComponent = UUtils::GetShooterPlayerComponent<UHealthComponent>(GetOwningPlayerPawn());
	if(!HealthComponent) return false;
	return HealthComponent->GetHealthPercent();
}

bool UPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = UUtils::GetShooterPlayerComponent<UWeaponComponent>(GetOwningPlayerPawn());
	if(!WeaponComponent) return false;
	return WeaponComponent->GetWeaponUIData(UIData);
}


bool UPlayerHUDWidget::GetCurrentAmmoData(FAmmoData& CurrentAmmo) const
{
	const auto WeaponComponent = UUtils::GetShooterPlayerComponent<UWeaponComponent>(GetOwningPlayerPawn());
	if(!WeaponComponent) return false;
	return WeaponComponent->GetWeaponUIAmmoData(CurrentAmmo);
}

bool UPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = UUtils::GetShooterPlayerComponent<UHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool UPlayerHUDWidget::IsPlayerSpectator() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

bool UPlayerHUDWidget::Initialize()
{

	if(GetOwningPlayer())
	{
		//получаю сылку на делигат нью паун и бинд функции
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UPlayerHUDWidget::OnNewPawn);

		OnNewPawn(GetOwningPlayerPawn());
	}
	
	return Super::Initialize();
}

void UPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if(HealthDelta<0.0f)
	{
		OnTakeDamage();
	}

}

void UPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
	const auto HealthComponent = UUtils::GetShooterPlayerComponent<UHealthComponent>(NewPawn);
	if(HealthComponent /*&& !HealthComponent->OnHealthChanged.IsBoundToObject(this)*/)
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &UPlayerHUDWidget::OnHealthChanged);
	}
}



