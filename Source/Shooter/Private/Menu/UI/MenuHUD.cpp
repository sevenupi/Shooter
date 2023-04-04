// First shooter developed by Sevenupi


#include "Menu/UI/MenuHUD.h"
#include "Blueprint/UserWidget.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if(MenuWidgetClass)
	{
		const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
		if(MenuWidget)
		{
			MenuWidget->AddToViewport();
		}
	}
}
