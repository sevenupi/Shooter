// First shooter developed by Sevenupi


#include "UI/GoToMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogGoToMenuWidget, All, All);

void UGoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &UGoToMenuWidget::GoToMenu);
	}
}

void UGoToMenuWidget::GoToMenu()
{
	if(!GetWorld()) return;
	
	const auto GameInstance = GetWorld()->GetGameInstance<UShooterGameInstance>();
	if(!GameInstance) return;

	if(GameInstance->GetMenuLevelName().IsNone())
	{
		UE_LOG(LogGoToMenuWidget, Error, TEXT("Menu level name is none"));
		return;
	}

	UGameplayStatics::OpenLevel(this, GameInstance->GetMenuLevelName());
}
