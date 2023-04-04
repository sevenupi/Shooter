// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Shooter/Public/ShooterCoreTypes.h"
#include "ShooterGameModeBase.generated.h"


class AAIController;
UCLASS()
class SHOOTER_API AShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShooterGameModeBase();


	FOnMatchStateChangeSignature OnMatchStateChange;
	virtual void StartPlay() override;

	/** returns default pawn class for given controller */
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	/** select best spawn point for player */
	//virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	
	void Killed(AController* KillerController, AController* VictimController);

	FGameData GetGameData() const { return GameData;}
	int32 GetCurrentRoundNum() const { return CurrentRound;}
	int32 GetRoundSecondsRemaining() const { return RoundCountDown;}

	void RespawnRequest(AController* Controller);

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate) override;
	virtual bool ClearPause() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category="Game")
	TSubclassOf<APawn> AIPawnClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Game")
	FGameData GameData;

private:
	EMatchState MatchState = EMatchState::WaitingToStart;
	
	int32 CurrentRound=1;
	int32 RoundCountDown =0;
	FTimerHandle GameRoundTimerHandle;

	
	void SpawnBots();
	void StartRound();
	void GameTimerUpdate();

	void ResetPlayers();
	void ResetOnePlayer(AController*  Controller);

	void CreateTeamsInfo();
	FLinearColor DetermineColorByTeamID(int32 TeamID) const;
	void SetPlayerColor(AController* Controller);

	void LogPlayerInfo();

	void StartRespawn(AController* Controller);
	
	void GameOver();
	void SetMatchState(EMatchState State);
};
