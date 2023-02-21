// First shooter developed by Sevenupi


#include "Weapon/RifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

void ARifleWeapon::StartFire()
{

	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ARifleWeapon::MakeShot, TimeBetweenShots,true);
	MakeShot();
}

void ARifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ARifleWeapon::MakeShot()
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
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}
	DecreaseAmmo();
}

bool ARifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
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
void ARifleWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamageActor = HitResult.GetActor();
	if(!DamageActor) return;

	DamageActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}