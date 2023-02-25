// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTER_API ABasePickup : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

protected:

	UPROPERTY(VisibleAnywhere, Category="Pickup")
	USphereComponent* CollisionComponent;
	
	UPROPERTY(EditAnywhere, Category="Pickup")
	float SphereRadius = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
	float RespwanTime = 5.0f;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	virtual bool GivePickUpTo(APawn* PlayerPawn);
	void PickUpWasTaken();
	void Respawn();
	float RotationYaw = 0.0f;
	void GenerateRotationYaw();
};
