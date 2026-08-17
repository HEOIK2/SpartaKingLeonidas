#include "Sirius.h" // 그러니까 이 소스는 시리우스 액터가 생성될 때 씬루트가 만들어지고, 그걸 루트 컴포넌트로 지정하고 그리고 스태틱메쉬컴포넌트가 만들어지고 그걸 씬루트 밑에 붙인다.
					// 그리고 BeginPlay는 그냥 호출되고 아무 효과가 없고, Tick 마다 델타타임을 
#include "Components/StaticMeshComponent.h"

ASirius::ASirius() // 앞에 놈이 클래스 뒤에 놈이 함수이다. 여기서는 생성자가 되겠죠. ASirius 클래스의 ASirius 생성자라는 뜻.
{
	PrimaryActorTick.bCanEverTick = true; // PrimaryActorTick: AActor가 갖고있는 멤버변수(구조체)다. Tick 관련 설정이 담겨있다/ bCanEverTick: 그 안의 스위치다. 접두사 b는 bool의 컨벤션
	// CanEverTick = Tick을 할 수 있긴한가? (한국어로) 자격을 말하는 것임. 이 엑터가 Tick이라는 걸 할 수가 있어? 이걸 꺼놓으면 Tick이 작동이 안된다. 성능 때문에 고안된 장치.
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")); // SceneRoot라는 포인터 변수에 SceneRoot라는 이름의 USceneComponent 타입의 주소값을 CreateDefalutSubobject 함수를 써서 넣어준다.
	// 그 밖에 CreateDefaultSubobject 함수가 하는 일 
	// 1. GC 등록(언리얼은 가비지 컬렉터가 메모리를 관리한다. 이 함수로 만들어야 GC로 추적해준다. new로 만들면 GC 밖에 있어서 누수가 나거나 크래시남)
	// 2. 에디터 연결 ㅡ Details 패널에 이 컴포넌트를 띄우고, 값을 저장/복원할 수 있게 등록.
	// 3. CDO 등록 ㅡ Default = CDO(Class Default Object)를 위한 것. 언리얼은 클래스마다 원본 견본품 하나를 미리 만들어 둔다. 그게 CDO다. 레벨에 액터를 배치하면, 엔진이 CDO를 복제해서 인스턴스를 만든다.
	// 생성자는 CDO를 만들 때 실행된다. 그래서 컴포넌트는 반드시 생성자에서만 CreateDefaultSubobject로 만들어야 한다. 다른 곳에서 만들면 크래시남.
	// Subobject = 액터에 종속된 하위 객체. 컴포넌트는 혼자 존재 못하고 항상 어떤 액터에 속한다.
	// 이해했다. 그러니까 CDO라는 것에 Subobject로 만들어 놔야 하는데 그게 생성자 주기때 생겨나니까 이때 만들어 넣어야 한다는거구나?
	// <USceneComponet>는 템플릿이다. 만들 타입만 갈아 끼우는 거다. 반환 타입도 자동으로 맞춰져서 형번환 없이 바로 대입된다.
	
	SetRootComponent(SceneRoot); // SceneRoot 컴포넌트를 루트컴포넌트로 지정하는 함수

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(SceneRoot); // 스태틱매쉬 컴포넌트를 씬루트 컴포넌트에 붙여주는 함수.
}

void ASirius::BeginPlay()
{
	Super::BeginPlay(); // Super는 부모클래스의 별명이다. GENERATED_BODY()가 자동으로 만들어준다. UHT가 만든 .generated.h 안에 있는 typedef다. - ASirius 에서는 Super = AActor. 
	// 왜 부르나요? 부모의 Tick/BeginPlay 안에는 엔진이 돌려야 하는 내부 로직이 들어가 있다. 안부르면 컴포넌트 Tick이 안돌거나, 타이머, 이벤트가 누락된다.
	GetWorld()->GetTimerManager().SetTimer(
		ToggleTimerHandle,
		this,
		&ASirius::ToggleVisibility,
		ToggleInterval,
		true
		
	);
	RotationSpeed = FMath::RandRange(30.f, 180.f);
}

void ASirius::ToggleVisibility()
{
	const bool bNowHidden = !IsHidden();
	SetActorHiddenInGame(bNowHidden);
	SetActorEnableCollision(!bNowHidden);
}

void ASirius::Tick(float DeltaTime) // 공식: 속도(초당) × DeltaTime = 이번 프레임에 처리할 양
// 프레임 당 각도는 다른데 1초의 결과는 같게 한다. = 프레임 독립성.
// 120fps -> DeltaTime = 1/120 -> 이번 프레임 몫 = 90 x (1/120) = 0.75도
// 30fps -> DeltaTime = 1/30 -> 이번 프레임 몫 = 90 x (1/30) = 3도
// 델타(Δ)는 수학 물리에서 "변화량"을 뜻하는 기호다 Δt  = 시간의 변화량 = 지난 프레임부터 지금까지 흐른 시간.
// 여기서 DeltaTime은 함수의 매개변수다. 저기에 heoik을 쓰던 뭐던 Tick 자체에서 DeltaTime으로 계산되게 한다.
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f)); // FRotator = 회전을 담는 구조체. 접두사 F는 구조체다. 인자 3개, 순서고정 FRotator(Pitch, Yaw, Roll) YZX임 |/_ 순서대로
	// Add 더한다 Actor 액터를 Local 로컬로 Rotation 회전 // 여기서 Set은 90으로 정하는 것이고, Add는 90을 더하는 것이다.
}

