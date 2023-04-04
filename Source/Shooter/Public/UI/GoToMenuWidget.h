// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GoToMenuWidget.generated.h"

class UButton;
UCLASS()
class SHOOTER_API UGoToMenuWidget : public UUserWidget
{
	GENERATED_BODY()


	
protected:
	UPROPERTY(meta=(BindWidget))
	UButton* GoToMenuButton;

	virtual void NativeOnInitialized() override;
	
private:
	UFUNCTION()
	void GoToMenu();
};
