// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "ShooterPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AShooterPlayerStart : public APlayerStart
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditInstanceOnly, Category = "TeamID")
	int32 TeamID = 1;

public:
	int32 GetTeamID() const {return TeamID;} 
};
