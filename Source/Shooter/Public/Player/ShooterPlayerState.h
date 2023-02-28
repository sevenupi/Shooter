// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ShooterPlayerState.generated.h"


UCLASS()
class SHOOTER_API AShooterPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void SetTeamID(int32 ID) {TeamID = ID;}
	int32 GetTeamID() const	{ return TeamID;}

	void SetTeamColor(const FLinearColor Color) {TeamColor = Color;}
	FLinearColor GetTeamColor() const	{ return TeamColor;}

	void AddKill(){ ++KillsNum; }
	int32 GetKillsNum() const	{ return KillsNum; }
	
	void AddDeaths(){++DeathsNum;}
	int32 GetDeathsNum() const	{ return DeathsNum; }

	void LogInfo();
	
private:
	int32 TeamID;
	FLinearColor TeamColor;

	int32 KillsNum;
	int32 DeathsNum;
};
