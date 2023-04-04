// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatRowWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class SHOOTER_API UPlayerStatRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPlayerName(const FText& Text);
	void SetKills(const FText& Text);
	void SetDeaths(const FText& Text);
	void SetTeam(const FText& Text);
	void SetPlayerIndicator(bool Visible);
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* PlayerNameTextBlock;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* KillsTextBlock;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* DeathTextBlock;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TeamTextBlock;
	
	UPROPERTY(meta=(BindWidget))
	UImage* PlayerIndicatorImage;
	
};
