// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "ShooterCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"



UCLASS()
class SHOOTER_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="UI")
	float Get_HealthPercent()const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool GetCurrentAmmoData (FAmmoData& CurrentAmmo) const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool IsPlayerSpectator() const;
	
	UFUNCTION(BlueprintImplementableEvent, Category="UI") // Создает ивент в блюпринт на основе этой функции
	void OnTakeDamage();
	
	virtual void NativeOnInitialized() override;

private:
	void OnHealthChanged(float Health, float HealthDelta);
	void OnNewPawn(APawn* NewPawn);
};
