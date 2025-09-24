// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGamemodeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddScore, int32, CurrentScore);

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API AShootingGamemodeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	int32 CurrentScore = 0;
	
	FOnAddScore OnAddScore;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainWidget> MainWidgetClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMenuWidget> MenuWidgetClass;

	class UMainWidget* MainWidgetInstance;
	class UMenuWidget* MenuWidgetInstance;
public:
	void AddScore(int32 Point); 
	void ShowMenu();
	void GamePaused();

	UFUNCTION()
	void GameRestart();
    UFUNCTION()
	void GameQuit();
};
