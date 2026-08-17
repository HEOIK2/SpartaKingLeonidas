#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "LeoPawn.generated.h"

class USphereComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;

UCLASS()
class SPARTAKINGLEONIDAS_API ALeoPawn : public APawn
{
	GENERATED_BODY()

public:
	ALeoPawn();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* SkeltalMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 500.f;

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void Up(const FInputActionValue& value);
	void Turn(const FInputActionValue& value);

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* UpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* TurnAction;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SpinSpeed = 30.f;

	UPROPERTY(EditAnywhere, Category = "Gravity")
	float Gravity = -980.f;

	UPROPERTY(EditAnywhere, Category = "Gravity")
	float GroundTraceDistance = 60.f;

	UPROPERTY(EditAnywhere, Category = "Gravity")
	float AirControlRatio = 0.4f;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* FlightAction;

	void Toggle(const FInputActionValue& value);

	bool bFlightMode = true;
	bool bIsGrounded = false;
	float ZVelocity = 0.f;
};
