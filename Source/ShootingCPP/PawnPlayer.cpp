// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnPlayer.h"
#include "Components/BoxComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Bullet.h"


// Sets default values
APawnPlayer::APawnPlayer() // 생성자 함수
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// BoxComp 변수에 객체를 생성해서 주소를 넣어준다.
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	// SetRootComponent는 매개변수의 컴포넌트를 현재 클래스 (APawnPlayer)의 루투 컴포넌트로 만든다.
	SetRootComponent(BoxComp);

	FVector BoxSize = FVector(50.0f, 50.0f, 50.0f);
	BoxComp->SetBoxExtent(BoxSize);
	BoxComp->SetGenerateOverlapEvents(true);
	BoxComp->SetCollisionProfileName(TEXT("PlayerProfile"));
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// ECC_GameTraceChannel1 세팅에서 만든 Player 오브젝트 채널
	BoxComp->SetCollisionObjectType(ECC_GameTraceChannel1); 
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static Mesh"));
	// SetupAttachment는 매개변수로 넣은 컴포넌트의 자식으로 본인을 할당한다.
	MeshComp->SetupAttachment(BoxComp); // (*). 랑 같다.

	FirePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Fire Position"));
	FirePosition->SetupAttachment(BoxComp);
}

// Called when the game starts or when spawned
void APawnPlayer::BeginPlay()
{
	Super::BeginPlay();

	// GetWorld는 현재 UWorld를 불러온다.
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	
	// ensure은 nullptr 체크 nullptr이면 크래쉬를 낸다.
	// check는 매개변수를 nullptr 체크하고 nullptr이면 에러 로그를 띄운다.
	//ensure(PlayerController);
	if (PlayerController != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
				PlayerController->GetLocalPlayer());
		if (Subsystem != nullptr)
		{
			Subsystem->AddMappingContext(IMC_PlayerInput, 0);
		}
	}

}

// Called every frame
void APawnPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 방향벡터 만들기
	FVector Direction = FVector(0.0f, HorizontalValue, VerticalValue);
	Direction.Normalize();

	// 이동 할 위치
	// getactorlocation : 현재 내 월드 좌표
	FVector NewLocation = GetActorLocation() + Direction * MoveSpeed * DeltaTime;

	// 결과 위치로 객체 이동 11
	SetActorLocation(NewLocation, true);




}

// Called to bind functionality to input
void APawnPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// Cast 위험한 작업
	UEnhancedInputComponent* EnhancedInputComponent =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// cast후에는 꼭 유효성 검사
	if (EnhancedInputComponent != nullptr)
	{
		EnhancedInputComponent->BindAction(IA_Horizontal, ETriggerEvent::Triggered,
			this, &APawnPlayer::OnInputHorizontal);
		EnhancedInputComponent->BindAction(IA_Horizontal, ETriggerEvent::Completed,
			this, &APawnPlayer::OnInputHorizontal);
		EnhancedInputComponent->BindAction(IA_Vertical, ETriggerEvent::Triggered,
			this, &APawnPlayer::OnInputVertical);
		EnhancedInputComponent->BindAction(IA_Vertical, ETriggerEvent::Completed,
			this, &APawnPlayer::OnInputVertical);
		
		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Started,
			this, &APawnPlayer::Fire);
	}
}

void APawnPlayer::OnInputHorizontal(const FInputActionValue& Value)
{
	HorizontalValue = Value.Get<float>();
	
}

void APawnPlayer::OnInputVertical(const FInputActionValue& Value)
{
    VerticalValue = Value.Get<float>();

}

void APawnPlayer::Fire()
{
	// SpawnActor : 월드에 Actor 상속받은 클래스를 생성하는 함수
	GetWorld()->SpawnActor<ABullet>(
		BulletFactory, // 생성할 객체의 클래스
		FirePosition->GetComponentLocation(), // 생성 월드 좌표
		FirePosition->GetComponentRotation() // 생성 될 회전값
	);

	float RandomPitch = FMath::FRandRange(0.7f, 1.5f);
	UGameplayStatics::PlaySound2D(GetWorld(), fireSound, RandomPitch);
}

