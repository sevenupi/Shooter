// First shooter developed by Sevenupi


#include "Componets/SCharacterMovementComponent.h"
#include "Player/ShooterBaseCharacter.h"

float USCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const AShooterBaseCharacter* Player = Cast<AShooterBaseCharacter>(GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
	
}

