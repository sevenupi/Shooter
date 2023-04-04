// First shooter developed by Sevenupi


#include "HitSphere.h"

// Sets default values
AHitSphere::AHitSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHitSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHitSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

