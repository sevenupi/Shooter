// First shooter developed by Sevenupi


#include "Weapon/LaserWeapon.h"
#include "Engine/World.h"
#include "Weapon/Components/WeaponFXComponent.h"

ALaserWeapon::ALaserWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<UWeaponFXComponent>("WeaponFXComponent");
}

void ALaserWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponFXComponent);
}
void ALaserWeapon::StartFire()
{

	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ALaserWeapon::MakeShot, TimeBetweenShots,true);
	MakeShot();
}

bool ALaserWeapon::TryToAmmoAddHealth(float HealthAmmoAmmount)
{
	return false;
}


void ALaserWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}



void ALaserWeapon::MakeShot()
{
	if(!GetWorld() || IsAmmoEmty())
	{
		StopFire();
		return;
	}
	
	FVector TraceStart, TraceEnd;
	if(!GetTraceData(TraceStart,TraceEnd))
	{
		StopFire();
		return;
	}
	
	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
	
	if(HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
		WeaponFXComponent->PlayImpactFX(HitResult);
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}
	DecreaseAmmo();
}

bool ALaserWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;
	
	TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad) ; // Конусовидное отклонение во время стрельбы
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}
void ALaserWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamageActor = HitResult.GetActor();
	if(!DamageActor) return;

//	DamageActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}


/*
void ALaserWeapon::LasserAmmoUpdate()
{
	if(isHealthFull() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

bool ALaserWeapon::isAmmohFull() const
{
	return FMath::IsNearlyEqual( Health , MaxHealth);
}
*/
