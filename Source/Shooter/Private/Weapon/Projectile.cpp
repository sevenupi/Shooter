// First shooter developed by Sevenupi


#include "Weapon/Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogProjectile, All, All);

AProjectile::AProjectile()
{
 	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("ShpereComponent");
	CollisionComponent->InitSphereRadius(SphereRadius);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SetRootComponent(CollisionComponent);

	MovementComponent= CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	MovementComponent->InitialSpeed = 10.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;
}


void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(MovementComponent);
	check(CollisionComponent);
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnProjectileHit);
UE_LOG(LogProjectile, Display, TEXT("Movement speed: %s"), *MovementComponent->Velocity.ToString())
	SetLifeSpan(LifeSeconds);
}

void AProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(!GetWorld()) return;
	MovementComponent->StopMovementImmediately();
	//make damage
	UGameplayStatics::ApplyRadialDamage(GetWorld(),DamageAmount, GetActorLocation(), DamageRadius, UDamageType::StaticClass(), {}, this, GetController(), DoFullDamage);
DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor
	::Orange, false, 5.0f );
	Destroy();
}

AController* AProjectile::GetController() const
{
	const auto Pawn= Cast<APawn>(GetOwner());
	return  Pawn ? Pawn->GetController() : nullptr;
}

