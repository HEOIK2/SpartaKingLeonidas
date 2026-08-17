#include "LeoGameMode.h"
#include "LeoPawn.h"

ALeoGameMode::ALeoGameMode()
{
	DefaultPawnClass = ALeoPawn::StaticClass();

}

void ALeoGameMode::BeginPlay()
{
	Super::BeginPlay();


	for (int32 i = 0; i < SpawnCount; ++i)
	{
		const FVector Loc(
			FMath::RandRange(-2000.f, 2000.f),
			FMath::RandRange(-2000.f, 2000.f),
			FMath::RandRange(100.f, 600.f)
		);

		const FRotator Rot(0.f, FMath::RandRange(0.f, 360.f), 0.f);

		UClass* PickedClass = (i % 2 == 0) ? SiriusClass : PerseusClass;
		if (PickedClass)
		{
			GetWorld()->SpawnActor<AActor>(PickedClass, Loc, Rot);
		}
	}
}