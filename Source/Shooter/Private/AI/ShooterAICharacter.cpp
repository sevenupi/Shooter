// First shooter developed by Sevenupi


#include "AI/ShooterAICharacter.h"
#include "Weapon/AIWeaponComponent.h"
#include "AI/ShooterAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BrainComponent.h"

AShooterAICharacter::AShooterAICharacter(const FObjectInitializer& objInit): Super(objInit.SetDefaultSubobjectClass<UAIWeaponComponent>("WeaponComponent"))
{
	
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = AShooterAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

void AShooterAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto ShooterAIController = Cast<AAIController>(Controller);
	if(ShooterAIController && ShooterAIController->BrainComponent)
	{
		ShooterAIController->BrainComponent->Cleanup(); // Остановка три бихейвора
	}
}
