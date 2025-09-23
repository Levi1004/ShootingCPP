// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFactory.h"
#include "Enemy.h"

// Sets default values
AEnemyFactory::AEnemyFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyFactory::BeginPlay()
{
	Super::BeginPlay();

	DelayTime = FMath::FRandRange(MinDelayTime, MaxDelayTime);

}

// Called every frame
void AEnemyFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentTime > DelayTime)
	{
		CurrentTime = 0.0f;
		// 적소환
		AEnemy* spawnActor = GetWorld()->SpawnActor<AEnemy>(EnemyClass,
			GetActorLocation(), GetActorRotation());
	}
	else
	{
		CurrentTime += DeltaTime;
	}
}

