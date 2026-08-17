#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LeoGameMode.generated.h"

UCLASS()
class SPARTAKINGLEONIDAS_API ALeoGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ALeoGameMode();

protected:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> SiriusClass;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> PerseusClass;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	int32 SpawnCount = 8;

	virtual void BeginPlay() override;
};