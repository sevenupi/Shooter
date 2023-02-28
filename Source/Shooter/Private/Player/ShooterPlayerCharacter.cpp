// First shooter developed by Sevenupi


#include "Player/ShooterPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapon/WeaponComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AShooterPlayerCharacter::AShooterPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
	CameraCollisionComponent->SetupAttachment(CameraComponent);
	CameraCollisionComponent->SetSphereRadius(10.0f);
	CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CameraCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AShooterPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(CameraCollisionComponent);

	CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AShooterPlayerCharacter::OnCameraCollisionBeginOverlap);
	CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AShooterPlayerCharacter::OnCameraCollisionEndOverlap);
}

void AShooterPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckCameraOverlap();
}

void AShooterPlayerCharacter::OnCameraCollisionEndOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckCameraOverlap();
}
void AShooterPlayerCharacter::CheckCameraOverlap()
{
	const auto HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
	GetMesh()->SetOwnerNoSee(HideMesh);

	TArray<USceneComponent*> MeshChildren;
	GetMesh()->GetChildrenComponents(true, MeshChildren);

	for (auto MeshChild : MeshChildren)
	{
		if (const auto MeshChildGeometry = Cast<UPrimitiveComponent>(MeshChild))
		{
			MeshChildGeometry->SetOwnerNoSee(HideMesh);
		}
	}
}
// Called to bind functionality to input
void AShooterPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	check(WeaponComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AShooterPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnArround", this, &AShooterPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AShooterPlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Run",IE_Pressed,this, &AShooterPlayerCharacter::OnStartRunning );
	PlayerInputComponent->BindAction("Run",	IE_Released  ,this, &AShooterPlayerCharacter::OnStopRunning );
	PlayerInputComponent->BindAction("Fire", IE_Pressed  ,WeaponComponent, &UWeaponComponent::StartFire );
	PlayerInputComponent->BindAction("Fire", IE_Released  ,WeaponComponent, &UWeaponComponent::StopFire );
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed  ,WeaponComponent, &UWeaponComponent::NextWeapon );
	PlayerInputComponent->BindAction("Reload", IE_Pressed  ,WeaponComponent, &UWeaponComponent::Reload );
}

void AShooterPlayerCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;
	if (Amount ==0.0f) return;
	AddMovementInput(GetActorForwardVector(), Amount);

	if (IsRunning() /*&& WeaponComponent->IsFiring()*/)
	{
		WeaponComponent->StopFire();
	}
}

void AShooterPlayerCharacter::MoveRight(float Amount)
{
	if(Amount ==0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void AShooterPlayerCharacter::OnStartRunning()
{
	WantsToRun = true;

	if (IsRunning())
	{
		WeaponComponent->StopFire();
	}
}

void AShooterPlayerCharacter::OnStopRunning()
{
	WantsToRun = false;
}

bool AShooterPlayerCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

void AShooterPlayerCharacter::OnDeath()
{
	Super::OnDeath();
	if(Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void AShooterPlayerCharacter::OnStartFire()
{
	if (IsRunning()) return;
	WeaponComponent->StartFire();
}