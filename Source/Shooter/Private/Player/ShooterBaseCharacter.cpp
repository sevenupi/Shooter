// First shooter developed by Sevenupi


#include "ShooterBaseCharacter.h"

#include <string>

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Componets/SCharacterMovementComponent.h"
#include "Componets/HealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharecterLog, All, All)

// Sets default values
AShooterBaseCharacter::AShooterBaseCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit.SetDefaultSubobjectClass<USCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

	HealthTextComponent=CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AShooterBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());

	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &AShooterBaseCharacter::OnDeath);
	HealthComponent -> OnHealthChanged.AddUObject(this, &AShooterBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &AShooterBaseCharacter::OnGroundLanded);
}

// Called every frame
void AShooterBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AShooterBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnArround", this, &AShooterBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AShooterBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run",IE_Pressed,this, &AShooterBaseCharacter::OnStartRunning );
	PlayerInputComponent->BindAction("Run",	IE_Released  ,this, &AShooterBaseCharacter::OnStopRunning );
}

bool AShooterBaseCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float AShooterBaseCharacter::GetMovementDiraction() const
{
	if (GetVelocity().IsZero()) return 0.0f;
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

	const auto Degrees = FMath:: RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void AShooterBaseCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount>0.0f;
	if(Amount ==0.0f) return;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AShooterBaseCharacter::MoveRight(float Amount)
{
	if(Amount ==0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void AShooterBaseCharacter::OnStartRunning()
{
	WantsToRun = true;
}

void AShooterBaseCharacter::OnStopRunning()
{
	WantsToRun = false;
}

void AShooterBaseCharacter::OnDeath()
{
	UE_LOG(BaseCharecterLog, Display, TEXT("Player %s is dead"), *GetName());
	
	PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(LifeSpanOnDeath);

	if(Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void AShooterBaseCharacter::OnHealthChanged(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"),Health)));
}

void AShooterBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{const auto Result = FMath::GetMappedRangeValueClamped(FVector2D(30.0f, 60.0f), FVector2D(200.0f, 500.0f), 45.0f);
	UE_LOG(BaseCharecterLog, Display, TEXT("%.1f"), Result);
	const auto FallVelocityZ = -GetVelocity().Z;
	UE_LOG(BaseCharecterLog, Display, TEXT("On Landed: %f"), FallVelocityZ);

	if(FallVelocityZ < LandedDamageVelocity.X) return;

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	UE_LOG(BaseCharecterLog, Display, TEXT("FinalDamage: %f"), FinalDamage);
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}







