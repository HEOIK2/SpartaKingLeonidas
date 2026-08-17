#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LeoPawn.generated.h"

UCLASS()
class SPARTAKINGLEONIDAS_API ALeoPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALeoPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
