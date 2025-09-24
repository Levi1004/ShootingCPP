// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "ShootingGamemodeBase.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	BoxComp->SetWorldScale3D(FVector(0.75f, 0.25f, 1.0f));
	BoxComp->SetCollisionProfileName(TEXT("BulletProfile"));
	
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	MeshComp->SetupAttachment(BoxComp);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletOverlap);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * MoveSpeed * DeltaTime;
	SetActorLocation(NewLocation);
}

void ABullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* CrashEnemy = Cast<AEnemy>(OtherActor);
	
	if (CrashEnemy != nullptr)
	{
        CrashEnemy->Destroy();

		AGameModeBase* CurrentGameModeBase = GetWorld()->GetAuthGameMode();

		AShootingGamemodeBase* ShootingGamemodeBase = Cast<AShootingGamemodeBase>(CurrentGameModeBase);

		if (ShootingGamemodeBase)
		{
			ShootingGamemodeBase->AddScore(1);
		}

		// UGameplaystatics 클래스 타입
		// SpawnEmitterAtLocation Static 함수, 클래스에 포함되는 함수
		// Getworld() : 현재 UWorld 오브젝트
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionFx, GetActorLocation(), GetActorRotation());

	
	}
	Destroy();
}


