// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShooterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FName GetStartUpLevelName()const{return StartUpLevelName;}
	FName GetMenuLevelName()const{return MenuLevelName;}

protected:
	UPROPERTY(EditDefaultsOnly, Category="Game")
	FName StartUpLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category="Game")
	FName MenuLevelName = NAME_None; 
	
};
