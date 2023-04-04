// First shooter developed by Sevenupi


#include "ShooterPlayerController.h"
#include "ShooterGameModeBase.h"
#include "RespawnComponent.h"

AShooterPlayerController::AShooterPlayerController()
{
	RespawnComponent= CreateDefaultSubobject<URespawnComponent>("RespawnComponent");
}

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(GetWorld())
	{
		const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->OnMatchStateChange.AddUObject(this, &AShooterPlayerController::OnMatchStateChange);
		}
	}
}

void AShooterPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OnNewPawn.Broadcast(InPawn);
}

void AShooterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if(!InputComponent) return;

	InputComponent->BindAction("Pause", IE_Pressed, this, &AShooterPlayerController::OnPauseGama);
}

void AShooterPlayerController::OnPauseGama()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void AShooterPlayerController::OnMatchStateChange(EMatchState State)
{
	if(State == EMatchState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}
