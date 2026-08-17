#include "LeoPawn.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Components/StaticMeshComponent.h"



ALeoPawn::ALeoPawn()
{
	PrimaryActorTick.bCanEverTick = true;


	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(SphereComp);
	SphereComp->SetSimulatePhysics(false);

	SkeltalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeltalMesh"));
	SkeltalMeshComp->SetupAttachment(SphereComp);
	SkeltalMeshComp->SetSimulatePhysics(false);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(SphereComp);
	SpringArmComp->TargetArmLength = 300.f;
	SpringArmComp->bUsePawnControlRotation = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SphereComp);
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ALeoPawn::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

void ALeoPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALeoPawn::Move);
		}
		if (LookAction)
		{
			EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALeoPawn::Look);
		}
		if (UpAction)
		{
			EnhancedInput->BindAction(UpAction, ETriggerEvent::Triggered, this, &ALeoPawn::Up);
		}
		if (TurnAction)
		{
			EnhancedInput->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ALeoPawn::Turn);
		}		
		if (FlightAction)
		{
			EnhancedInput->BindAction(FlightAction, ETriggerEvent::Started, this, &ALeoPawn::Toggle);
		}
	}
}

void ALeoPawn::Move(const FInputActionValue& value)
{
	const FVector2D Input = value.Get<FVector2D>();
	const float Delta = GetWorld()->GetDeltaSeconds();

	if (Input.IsNearlyZero()) return;

	const float Multiplier = (bFlightMode || bIsGrounded) ? 1.f : AirControlRatio;

	AddActorLocalOffset(FVector(Input.X, Input.Y, 0.f) * MoveSpeed * Multiplier * Delta, true);
}

void ALeoPawn::Look(const FInputActionValue& value)
{
	const FVector2D Input = value.Get<FVector2D>();

	AddActorLocalRotation(FRotator(0.f, Input.X, 0.f));
	SpringArmComp->AddLocalRotation(FRotator(Input.Y, 0.f, 0.f));
}

void ALeoPawn::Up(const FInputActionValue& value)
{
	if (!bFlightMode) return;
	const float Input = value.Get<float>();
	const float Delta = GetWorld()->GetDeltaSeconds();

	if (!FMath::IsNearlyZero(Input))
	{
		AddActorLocalOffset(FVector(0.f, 0.f, Input) * MoveSpeed * Delta, true);
	}
}

void ALeoPawn::Turn(const FInputActionValue& value)
{
	const float Input = value.Get<float>();
	const float Delta = GetWorld()->GetDeltaSeconds();
	const float RollAmount = Input * 60.f * Delta;

	AddActorLocalRotation(FRotator(0.f, 0.f, RollAmount));
	SpringArmComp->AddLocalRotation(FRotator(0.f, 0.f, -RollAmount));
}

void ALeoPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StaticMesh->AddLocalRotation(FRotator(0.f, SpinSpeed * DeltaTime, 0.f));

	if (bFlightMode)
	{
		bIsGrounded = false;
		ZVelocity = 0.f;
		return;
	}

	FHitResult Hit;
	const FVector Start = GetActorLocation();
	const FVector End = Start - FVector(0.f, 0.f, GroundTraceDistance);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bIsGrounded = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

	if (bIsGrounded)
	{
		if (ZVelocity < 0.f)
		{
			ZVelocity = 0.f;
		}
	}
	else
	{
		ZVelocity += Gravity * DeltaTime;
		AddActorWorldOffset(FVector(0.f, 0.f, ZVelocity * DeltaTime), true);
	}
}
void ALeoPawn::Toggle(const FInputActionValue& value)
{
	bFlightMode = !bFlightMode;
	ZVelocity = 0.f;
}