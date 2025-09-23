// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "EngineUtils.h"
#include "PawnPlayer.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	// SetRootComponent는 매개변수의 컴포넌트를 현재 클래스 (APawnPlayer)의 루투 컴포넌트로 만든다.
	SetRootComponent(BoxComp);

	FVector BoxSize = FVector(50.0f, 50.0f, 50.0f);
	BoxComp->SetBoxExtent(BoxSize);
	BoxComp->SetCollisionProfileName(TEXT("EnemyProfile"));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static Mesh"));
	// SetupAttachment는 매개변수로 넣은 컴포넌트의 자식으로 본인을 할당한다.
	MeshComp->SetupAttachment(BoxComp); // (*). 랑 같다.

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	int32 DrawResult = FMath::RandRange(1, 100);
	if (DrawResult < TraceRate)
	{
		// 추첨 성공
		// 플레이어 방향으로 Direction 설정
		// 플레이어를 알아야 방향을 연산을 한다.
		// TActorIterator
		// T : 템플릿의 약자
		// TActor는 Actor 타입의 템플릿이라는 뜻
		// AActor 와 AActor를 상속받은 타입이 들어올 수 있다.
		// Iterator : 반복자 (예 : 배열)에 담긴 요소들을 순차적으로 접근할 수 있도록
		// 도와주는 객체

		// APawnPlayer와 APawnPlay의 자식 클래스가 할당 될 수 있는 
		// Iterator를 선언했고.
		// Iterator에 들어 갈 액터들은 GetWorld() 즉 현재 UWorld 범위에서 서치해왔다.		
		// 결론 현재 월드에 있는 APawnPlayer 타입을 전부 Iterator 등록을 시켜놨다.
		TActorIterator<APawnPlayer> Players(GetWorld());
		//for (TActorIterator<APlayerPawn> palyer(GetWorld()); player; ++player)


		// 초기화 식 : Players 변수를 넣는다.
		// 조건식 현재 Players가 nullptr인가\?
		// 증감식 ++Players : Iterator에 등록된 다음 객체로 넘어간다.


		for (Players; Players; ++Players)
		{
			// FString.Contains : 현재 문자열에 매개변수 문자를 포함하면 true
			// 포함하지 않으면 false
			if (Players->GetName().Contains("BP_PawnPlayer"))
			{
				Direction = Players->GetActorLocation() - GetActorLocation();
				Direction.Normalize();
			}
		}
	}
	else
	{
		// 추첨 실패
		// 정면 방향으로 Direction 설정
		Direction = GetActorForwardVector();
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + Direction * MoveSpeed * DeltaTime;
	SetActorLocation(NewLocation);

}

