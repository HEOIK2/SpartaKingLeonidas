#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sirius.generated.h"

UCLASS()
class SPARTAKINGLEONIDAS_API ASirius : public AActor // 이 클래스를 다른 모듈에도 쓸 수 있게 해줍니다.
{
	GENERATED_BODY()
	
public:	
	ASirius(); // 생성자입니다. 클래스와 이름이 같고 반환 타입이 없는 함수입니다. 객체가 만들어질 때 딱 한 번 호출됩니다.
	virtual void Tick(float DeltaTime) override; 
	// Tick은 이미 AActor에서 Virtual로 선언되어 있다. AActor가 갖고 있는 Virtual 함수를 재정의(덮어쓰기) 하는 선언이다.
	// Virtual: 엔진이 AActor* 포인터로 불러도 내 버전(ASirius::Tick)이 실행되게 함.
	// 이름 뜻이 virtual 가상의, 실체는 없지만 그런 것처럼 작동하는. 이라는 뜻인데 여기선 "함수 호출이 어디로 갈지, 컴파일 시점엔 실체가 정해지지 않았다."라는 뜻이란다.
	// 원래 일반함수는 컴파일 시점에서 이 호출은 어디로 간다가 딱 박히는데 virtual은 그 자리를 비워두고 실행할 때 채운다고 한다. "나중에 정해지는 함수"
	//			없으면 부모 버전이 실행되어서 내 코드가 실행되지 않는다.
	// override: "부모에 이 함수가 진짜 있는지" 컴파일러가 검사해줌. 오타 방지용 공짜 안전장치다. 재정의란? 부모함수를 내 버전으로 바꾼다! 라는 뜻.

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category = "Components") // UPROPERY: 변수를 리플렉션 하는 매크로
	USceneComponent* SceneRoot; // 멤버변수 SceneRoot는 USceneComponent라는 클래스 타입의 포인터다.

	UPROPERTY(VisibleAnywhere, Category = "Components") // VisibleAnywhere: 어디서든 보이되, 수정은 불가. 여기서 어디는 클래스 디폴트와 인스턴스
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation") // Category는 Detail 패널의 그룹이름이다. 순전히 정리용.
	float RotationSpeed = 90.f; // .f 안하면 double이 된다네? 뭐 안해도 상관 없는데 넣는게 국룰인듯.

	UPROPERTY(EditAnywhere, Category = "Timer")
	float ToggleInterval = 2.f;

	FTimerHandle ToggleTimerHandle;

	void ToggleVisibility();

};
