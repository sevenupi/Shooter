// First shooter developed by Sevenupi


#include "UI/GameDataWidget.h"
#include "ShooterGameModeBase.h"
#include "ShooterPlayerState.h"

int32 UGameDataWidget::GetKillsNum() const
{
	const auto PlayerState = GetPlayerState();
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 UGameDataWidget::GetDeathsNum() const
{
	const auto PlayerState = GetPlayerState();
	return PlayerState ? PlayerState->GetDeathsNum() : 0;
}

int32 UGameDataWidget::GetCurrentRoundsNum() const
{
	const auto GameMode = GetGameMode();
	return GameMode ? GameMode ->GetCurrentRoundNum() : 0 ;
}

int32 UGameDataWidget::GetTotalRoundsNum() const
{
	const auto GameMode = GetGameMode();
	return GameMode ? GameMode->GetGameData().RoundsNum : 0 ;
}

int32 UGameDataWidget::GetRoundSecondsRemainig() const
{
	const auto GameMode = GetGameMode();
	return GameMode? GameMode->GetRoundSecondsRemaining() : 0 ;
}

AShooterGameModeBase* UGameDataWidget::GetGameMode() const
{
	return GetWorld() ? Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

AShooterPlayerState* UGameDataWidget::GetPlayerState() const
{
	return GetOwningPlayer() ? Cast<AShooterPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
