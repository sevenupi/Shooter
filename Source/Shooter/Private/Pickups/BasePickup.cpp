// First shooter developed by Sevenupi


#include "Pickups/BasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);


// Sets default values
ABasePickup::ABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionComponent = CreateDefaultSubobject<USphereComponent>("ShpereComponent");
	CollisionComponent->InitSphereRadius(SphereRadius);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();

	check(CollisionComponent);
	
	GenerateRotationYaw();
}

void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if(GivePickUpTo(Pawn))
	{
		//UE_LOG(LogBasePickup, Display, TEXT("Pickup was picked"));
		PickUpWasTaken();
	}


}

// Called every frame
void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, RotationYaw * DeltaTime, 0.0f));
}

bool ABasePickup::GivePickUpTo(APawn* PlayerPawn)	
{
	return false;
}


void ABasePickup::PickUpWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
	}
	FTimerHandle RespawntTimerHandle;
	GetWorldTimerManager().SetTimer(RespawntTimerHandle, this, &ABasePickup::Respawn, RespwanTime);
}

void ABasePickup::Respawn()
{	GenerateRotationYaw();
	
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void ABasePickup::GenerateRotationYaw()
{
	const auto Direction = FMath::RandBool() ? 1 : -1;
	RotationYaw = FMath::RandRange(50.0f,60.0f) * Direction;
}



