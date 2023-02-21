// First shooter developed by Sevenupi


#include "UI/GameHUD.h"
#include "Engine/Canvas.h"

void AGameHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawCrossHair();
}

void AGameHUD::DrawCrossHair()
{
	int32 SizeX = Canvas->SizeX;
	int32 SizeY = Canvas->SizeY;
	const TInterval<float> Center(SizeX*0.5f, SizeY*0.5f);
	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LinearColor = FLinearColor::Green;

	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LinearColor, LineThickness );
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LinearColor, LineThickness);
}
