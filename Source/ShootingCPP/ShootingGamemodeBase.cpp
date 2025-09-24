// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGamemodeBase.h"
#include "MainWidget.h"
#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void AShootingGamemodeBase::BeginPlay()
{
	Super::BeginPlay();

	if (MainWidgetClass != nullptr)
	{
		// À§Á¬ °´Ã¼È­
		MainWidgetInstance = CreateWidget<UMainWidget>(GetWorld(), MainWidgetClass);

		// È­¸é¿¡ Ãâ·Â
		if (MainWidgetInstance != nullptr) 
		{

			OnAddScore.AddDynamic(MainWidgetInstance, &UMainWidget::PrintScore);
			MainWidgetInstance->AddToViewport();
		}


	}
}

void AShootingGamemodeBase::AddScore(int32 Point)
{
	CurrentScore += Point;
	OnAddScore.Broadcast(CurrentScore);
}

void AShootingGamemodeBase::ShowMenu()
{
	if (MenuWidgetClass != nullptr)
	{
		MenuWidgetInstance = CreateWidget<UMenuWidget>(GetWorld(), MenuWidgetClass);
		
		if (MenuWidgetInstance != nullptr)
		{
			MenuWidgetInstance->AddListener(this);
			MenuWidgetInstance->AddToViewport();
		}
	}
}

void AShootingGamemodeBase::GamePaused()
{
	UWorld* CurrentWorld = GetWorld();

	CurrentWorld->GetFirstPlayerController()->SetShowMouseCursor(true);

	UGameplayStatics::SetGamePaused(CurrentWorld, true);
}

void AShootingGamemodeBase::GameRestart()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMap");
}

void AShootingGamemodeBase::GameQuit()
{
	UWorld* CurrentWorld = GetWorld();
	UKismetSystemLibrary::QuitGame(CurrentWorld, CurrentWorld->GetFirstPlayerController(),
		EQuitPreference::Quit, false);
}
