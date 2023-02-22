// First shooter developed by Sevenupi


#include "Componets/HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Development/FireDamageType.h"
#include "Development/IceDamageType.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)
// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check (MaxHealth> 0);
	SetHealth(MaxHealth);
	
	AActor* ComponentOwner = GetOwner();
	if(ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamageHandle);
	}
}
void UHealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage<=0 || IsDead()|| !GetWorld()) return;
	
	SetHealth(Health - Damage);
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if(AutoHeal)
	{
		GetWorld() -> GetTimerManager().SetTimer(HealTimerHandle, this, &UHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}
/* This code was for testing and future development
 * 
 *	UE_LOG(LogHealthComponent, Display, TEXT("Damage: %f"), Damage);
	if(DamageType)
	{
		if(DamageType->IsA<UFireDamageType>())
		{
			UE_LOG(LogHealthComponent, Display, TEXT("Fireeeeeeeeeeeeeeee!!!!!"));
		}
		else if(DamageType->IsA<UIceDamageType>())
		{
			UE_LOG(LogHealthComponent, Display, TEXT("FREEEZE , BR-BR-BR"));
		}
	} */

}

void UHealthComponent::HealUpdate()
{
	//if(IsDead()) return;
	SetHealth(Health + HealModifier);

	if(FMath::IsNearlyEqual( Health , MaxHealth) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void UHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}




