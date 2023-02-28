// First shooter developed by Sevenupi


#include "AI/ShooterAIController.h"

#include "Componets/RespawnComponent.h"
#include "AI/ShooterAICharacter.h"
#include "Componets/ShooterAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AShooterAIController::AShooterAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UShooterAIPerceptionComponent>("AIPerceptionComponent");
	SetPerceptionComponent(*AIPerceptionComponent);
	RespawnComponent= CreateDefaultSubobject<URespawnComponent>("RespawnComponent");
	
	bWantsPlayerState = true;
}

void AShooterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto AICharacter = Cast<AShooterAICharacter>(InPawn);
	if(AICharacter)
	{
		RunBehaviorTree(AICharacter->BehaviorTreeAsset);
	}
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

AActor* AShooterAIController::GetFocusOnActor() const
{
	if(!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>( GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
