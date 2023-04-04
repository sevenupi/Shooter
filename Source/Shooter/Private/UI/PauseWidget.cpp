// First shooter developed by Sevenupi


#include "UI/PauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

void UPauseWidget::NativeOnInitialized()
{

	Super::NativeOnInitialized();

	if(ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &UPauseWidget::OnClearPause);
	}

}

void UPauseWidget::OnClearPause()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}
