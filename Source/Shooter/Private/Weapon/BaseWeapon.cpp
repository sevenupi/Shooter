// First shooter developed by Sevenupi


#include "Weapon/BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void ABaseWeapon::StartFire()
{
	
}
void ABaseWeapon::StopFire()
{

}

void ABaseWeapon::MakeShot()
{
	
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	check(WeaponMesh);
	checkf(DefaultAmmo.Bullets>0, TEXT("Bullets count couldnt be leess or equel zero")) // такой же самый как Check только с сообщением
	CurrentAmmo = DefaultAmmo;
}



APlayerController* ABaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if(!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

bool ABaseWeapon:: GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto Controller = GetPlayerController();
	if(!Controller) return false;
	
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	return true;
}

FVector ABaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ABaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;
	
	TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector(); 
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void ABaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if(!GetWorld()) return;
	
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionQueryParams);

}

void ABaseWeapon::DecreaseAmmo()
{
	if(CurrentAmmo.Bullets == 0)
	{
		UE_LOG(LogBaseWeapon, Warning, TEXT("--------------CLIS IS EMPTY-------------"));
		return;
	}
	CurrentAmmo.Bullets--;
	LogAmmo();
	if(IsClipEmtry() && !IsAmmoEmty())
	{
		StopFire();
		OnclipEmty.Broadcast();
	}
}


bool ABaseWeapon::IsAmmoEmty() const
{
	return !CurrentAmmo.Infinite && CurrentAmmo.CLips ==0 && IsClipEmtry();
}

bool ABaseWeapon::IsClipEmtry() const
{
	return CurrentAmmo.Bullets ==0;
}

void ABaseWeapon::ChangeClip()
{

	if(!CurrentAmmo.Infinite)
	{
		if(CurrentAmmo.CLips == 0)
		{
			UE_LOG(LogBaseWeapon, Warning, TEXT("--------------NO MORE CLIPS-------------"));
			return;
		}
		CurrentAmmo.CLips --;
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	UE_LOG(LogBaseWeapon, Display, TEXT("--------------RELOADING CLIP-------------"));
}

bool ABaseWeapon::CanReload() const
{
	return  CurrentAmmo.Bullets< DefaultAmmo.Bullets && CurrentAmmo.CLips>0;
}

void ABaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo" + FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.CLips);
	UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
}

// for VR it will be works
void ABaseWeapon::GetMuzzleWorldLocationVR()
{
	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	const FVector TraceStart =SocketTransform.GetLocation();
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	
}

