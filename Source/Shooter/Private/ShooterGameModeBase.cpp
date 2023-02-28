// First shooter developed by Sevenupi


#include "ShooterGameModeBase.h"

#include "ChangeWeaponService.h"
#include "GameFramework/HUD.h"
#include "Player/ShooterBaseCharacter.h"
#include "Player/ShooterPlayerController.h"
#include "Ui/GameHUD.h"
#include "AIController.h"
#include "Player/ShooterPlayerState.h"
#include "Shooter/Public/Utils.h"
#include "Componets/RespawnComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameModeBase, All, All);

constexpr static int32 MinRoundTimeForRespawn = 10; //минимальное время раунда для респауна

AShooterGameModeBase::AShooterGameModeBase()
{
	DefaultPawnClass = AShooterBaseCharacter::StaticClass();
	PlayerControllerClass = AShooterPlayerController::StaticClass();
	HUDClass = AGameHUD::StaticClass();
	PlayerStateClass = AShooterPlayerState::StaticClass();
}

void AShooterGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	CreateTeamsInfo();
	
	CurrentRound = 1;
	StartRound();
}

UClass* AShooterGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AShooterGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
	const auto KillerPlayerState = KillerController ? Cast<AShooterPlayerState>(KillerController->PlayerState) : nullptr;
	const auto VictimPlayerState = VictimController ? Cast<AShooterPlayerState>(VictimController->PlayerState) : nullptr;

	if(KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}	
	
	if(VictimPlayerState)
	{
		VictimPlayerState->AddDeaths();
	}

	StartRespawn(VictimController);
}

void AShooterGameModeBase::RespawnRequest(AController* Controller)
{
	ResetOnePlayer(Controller);
}

void AShooterGameModeBase::SpawnBots()
{
	if(!GetWorld()) return;

	for(int32 i = 0; i<GameData.PlayersNum-1; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto ShooterAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(ShooterAIController);
	}
}

void AShooterGameModeBase::StartRound()
{
	RoundCountDown = GameData.Roundtime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AShooterGameModeBase::GameTimerUpdate, 1.0f, true);
}

void AShooterGameModeBase::GameTimerUpdate()
{
	UE_LOG(LogGameModeBase, Display, TEXT("Time: %i / Round: %i / %i "), RoundCountDown, CurrentRound, GameData.RoundsNum);

	if(--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (CurrentRound + 1 <= GameData.RoundsNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			UE_LOG(LogGameModeBase, Display, TEXT("-------------Game over-----------"));
			LogPlayerInfo();
		}
	}
}

void AShooterGameModeBase::ResetPlayers()
{
	if(!GetWorld()) return;

	for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
	
}

void AShooterGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void AShooterGameModeBase::CreateTeamsInfo()
{
	if(!GetWorld()) return;

	int32 TeamID = 1;
	for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if(!Controller) continue;;

		const auto PlayerState = Cast<AShooterPlayerState>(Controller->PlayerState);
		if(!PlayerState) continue;

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		SetPlayerColor(Controller);
		TeamID = TeamID == 1 ? 2 : 1;

	}
}

FLinearColor AShooterGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
	if(TeamID-1 < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[TeamID - 1];
	}
	UE_LOG(LogGameModeBase, Display, TEXT("No COlor For Team ID: %i, set to deafault:%s"), TeamID, *GameData.DefaultTeamColor.ToString());
	return GameData.DefaultTeamColor;
}

void AShooterGameModeBase::SetPlayerColor(AController* Controller)
{
	if(!Controller) return;

	const auto Character = Cast<AShooterBaseCharacter>(Controller->GetPawn());
	if(!Character) return;

	const auto PlayerState = Cast<AShooterPlayerState>(Controller->PlayerState);
	if(!PlayerState) return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void AShooterGameModeBase::LogPlayerInfo()
{

	if(!GetWorld()) return;
	
	for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if(!Controller) continue;;

		const auto PlayerState = Cast<AShooterPlayerState>(Controller->PlayerState);
		if(!PlayerState) continue;

		PlayerState->LogInfo();
	}
}

void AShooterGameModeBase::StartRespawn(AController* Controller)
{
	const auto RespawnAvailble = RoundCountDown > MinRoundTimeForRespawn + GameData.RespawnTime;
	if(!RespawnAvailble) return;
	const auto RespawnComponent = UUtils::GetShooterPlayerComponent<URespawnComponent>(Controller);
	if(!RespawnComponent) return;

	RespawnComponent->Respawn(GameData.RespawnTime);
}

