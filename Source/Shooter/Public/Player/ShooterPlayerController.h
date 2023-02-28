// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

class URespawnComponent;

UCLASS()
class SHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AShooterPlayerController();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	URespawnComponent* RespawnComponent;
};
