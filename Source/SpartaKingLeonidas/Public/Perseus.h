#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Perseus.generated.h"

UCLASS()
class SPARTAKINGLEONIDAS_API APerseus : public AActor
{
	GENERATED_BODY()
	
public:	
	APerseus();
	virtual void Tick(float DeltaTime) override;


protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 200.f; // 초당 200cm 이동. 언리얼의 기본 단위가 cm다. 사람 키가 대략 180이니가 200이면 적당히 눈에 보이는 속도.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxRange = 300.f; // 시작 위치에서 최대 300cm까지 갔다가 돌아옴. 왕복 총 거리는 600.

private:
	FVector StartLocation; // F접두사는 구조체. Fvector는 x,y,z  세개의 float을 묶은 것. 이건 왜 private이고 UPROPERTY가 없나? 이건 BeginPlay에서 자동으로
	// 채워지는 내부 상태값이다. 에디터에서 사람이 만질게 아님. 오히려 만지면 망가진다.
	int32 MoveDirection = 1; // 방향 스위치. 1이면 전진, -1이면 후진. int32는 언리얼이 정의한 타입이다. int를 써도 되는데, int 크기가 다를 수 있어서
	// 언리얼은 크기를 명시한 타입을 쓴다. int32는 어디서든 4바이트, 근데 왜 멤버변수인가? 하면 Tick은 매 프레임 다시 실행되기 때문에 함수 내의 지역변수로 삼으면
	// 매번 사라진다. 그래서 지금 어느 쪽으로 가는 중인가를 함수 밖에 저장해둬야 다음 프레임에도 남아있다.

};
