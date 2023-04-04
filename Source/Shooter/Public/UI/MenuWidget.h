// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class UButton;
UCLASS()
class SHOOTER_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta=(BindWidget))
	UButton* QuitGameButton;
	
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnQuitGame();
};
