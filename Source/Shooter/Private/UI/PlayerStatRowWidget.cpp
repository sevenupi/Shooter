// First shooter developed by Sevenupi


#include "UI/PlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UPlayerStatRowWidget::SetPlayerName(const FText& Text)
{
	if(!PlayerNameTextBlock) return;

	PlayerNameTextBlock->SetText(Text);
}

void UPlayerStatRowWidget::SetKills(const FText& Text)
{
	if(!KillsTextBlock) return;

	KillsTextBlock->SetText(Text);
}

void UPlayerStatRowWidget::SetDeaths(const FText& Text)
{
	if(!DeathTextBlock) return;

	DeathTextBlock->SetText(Text);
}

void UPlayerStatRowWidget::SetTeam(const FText& Text)
{
	if(!TeamTextBlock) return;

	TeamTextBlock->SetText(Text);
}

void UPlayerStatRowWidget::SetPlayerIndicator(bool Visible)
{
	if(!PlayerIndicatorImage) return;

	PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
