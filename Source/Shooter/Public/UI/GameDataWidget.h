// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "ShooterGameModeBase.h"
#include "ShooterPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "GameDataWidget.generated.h"

class AShooterGameModeBase;
class AShooterPlayerState;

UCLASS()
class SHOOTER_API UGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="UI")
	int32 GetKillsNum() const;
	
	UFUNCTION(BlueprintCallable, Category="UI")
	int32 GetDeathsNum() const;
	
	UFUNCTION(BlueprintCallable, Category="UI")
	int32 GetCurrentRoundsNum() const;
	
	UFUNCTION(BlueprintCallable, Category="UI")
	int32 GetTotalRoundsNum() const;
	
	UFUNCTION(BlueprintCallable, Category="UI")
	int32 GetRoundSecondsRemainig() const;

private:
	AShooterGameModeBase* GetGameMode() const;
	AShooterPlayerState* GetPlayerState() const;
	
};
