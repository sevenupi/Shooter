// First shooter developed by Sevenupi


#include "UI/MenuWidget.h"

#include "AIWeaponComponent.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ShooterGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogShooterMenuWidget, All, All);

void UMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UMenuWidget::OnStartGame);
	}
	if(QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UMenuWidget::OnQuitGame);
	}
}

void UMenuWidget::OnStartGame()
{

	if(!GetWorld()) return;
	
	const auto GameInstance = GetWorld()->GetGameInstance<UShooterGameInstance>();
	if(!GameInstance) return;

	if(GameInstance->GetStartUpLevelName().IsNone())
	{
		UE_LOG(LogShooterMenuWidget, Error, TEXT("Level is nullptr"));
		return;
	}

	UGameplayStatics::OpenLevel(this, GameInstance->GetStartUpLevelName());
}

void UMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
