#include "Perseus.h"
#include "Components/StaticMeshComponent.h"

APerseus::APerseus() // 생성할 때 CDO 할 때 컴포넌트 붙여서 루트로 삼고 거기에 또 컴포넌트 하나 만들어서 아래에 붙이기.
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(SceneRoot);
}

void APerseus::BeginPlay() // 그니까 게임 시작 할 때 (혹은 배치 직후) 현재 위치를 왕복의 기준 점으로 저장하는거임. 생성자에 만들면 0,0,0으로 나온다. 왜? 아직 월드배치 되기 전이라.
{
	Super::BeginPlay();
	MoveSpeed = FMath::RandRange(100.f, 400.f);
	MaxRange = FMath::RandRange(200.f, 800.f);
	StartLocation = GetActorLocation();

}

void APerseus::Tick(float DeltaTime) // 그니까 매 프레임 X축으로 조금씩 이동시키고, // 시작점에서 MaxRange만큼 벗어나면 방향을 뒤집어 왕복시킨다.
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation(); // 현재 위치를 복사해온다. 바로 안 움직이고 계산용 사본을 만드는 것.
	NewLocation.X += MoveSpeed * DeltaTime * MoveDirection; // MoveSpeed * DeltaTime = 이번 프레임 이동량 // * MoveDirection 방향 적용. 1이면 +, -1이면 -
	// .X니까 X축 방향으로만 움직임

	float DistanceMoved = FMath::Abs(NewLocation.X - StartLocation.X);
	// 시작점에서 얼마나 떨어졌는가. FMath::Abs는 절댓값. 뒤로 갈 때는 음수가 나오니까 부호를 없애야 거리로 비교된다.

	if (DistanceMoved >= MaxRange)
	{
		MoveDirection *= -1;
	}
	// 300cm(MaxRange)가 넘었으면 방향 뒤집기. *= -1은 1 -> -1, -1 -> 1 토글. 

	SetActorLocation(NewLocation); // 계산 끝난 위치를 실제로 적용.
}

