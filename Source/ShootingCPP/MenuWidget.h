// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ButtonRestart;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ButtonQuit;

public:
	void AddListener(class AShootingGameModeBase* GameMode);
};
