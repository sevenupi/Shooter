// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Shooter/Public/ShooterCoreTypes.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;
	
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	TMap<EMatchState, UUserWidget*> GameWidgets;
	UPROPERTY()
	UUserWidget* CurrentWidget = nullptr;
	void DrawCrossHair();
	void OnMatchStateChange(EMatchState State);
	
};
