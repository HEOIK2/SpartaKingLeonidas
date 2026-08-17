#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "LeoPawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;


UCLASS()
class SPARTAKINGLEONIDAS_API ALeoPawn : public APawn
{
	GENERATED_BODY()

public:
	ALeoPawn();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 500.f;

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
};
