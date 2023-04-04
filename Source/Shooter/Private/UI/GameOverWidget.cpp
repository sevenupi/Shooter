// First shooter developed by Sevenupi


#include "UI/GameOverWidget.h"
#include "Shooter/Public/ShooterGameModeBase.h"
#include "Player/ShooterPlayerState.h"
#include "UI/PlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "Shooter/Public/Utils.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"



void UGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if(GetWorld())
	{
		const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->OnMatchStateChange.AddUObject(this, &UGameOverWidget::OnMatchStateChange);
		}
	}

	if(ResetLevelButton)
	{
		ResetLevelButton->OnClicked.AddDynamic(this, &UGameOverWidget::UGameOverWidget::OnResetLevel);
	}
}

void UGameOverWidget::OnMatchStateChange(EMatchState State)
{
	if(State == EMatchState::GameOver)
	{
		UpdatePlayerStat();
	}
}

void UGameOverWidget::UpdatePlayerStat()
{
	if(!GetWorld() || !PlayerStatBox) return;

	//clear box list
	PlayerStatBox->ClearChildren();

	for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if(!Controller) continue;

		const auto PlayerState = Cast<AShooterPlayerState>(Controller->PlayerState);
		if(!PlayerState) continue;

		const auto PlayerStatRowWidget = CreateWidget<UPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
		if(!PlayerStatRowWidget) continue;

		PlayerStatRowWidget ->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStatRowWidget ->SetKills(UUtils::TextFromInt(PlayerState->GetKillsNum()));
		PlayerStatRowWidget ->SetDeaths(UUtils::TextFromInt(PlayerState->GetDeathsNum()));
		PlayerStatRowWidget ->SetTeam(UUtils::TextFromInt(PlayerState->GetTeamID()));
		PlayerStatRowWidget->SetPlayerIndicator(Controller->IsPlayerController());

		PlayerStatBox ->AddChild(PlayerStatRowWidget);
	}
}

void UGameOverWidget::OnResetLevel()
{
	//const FName CurrentLevelName = "TestLevel";
	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
