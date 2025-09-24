// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Components/Button.h"
#include "ShootingGameModeBase.h"

void UMenuWidget::AddListener(AShootingGameModeBase* GameMode)
{
    ButtonRestart->OnClicked.AddUniqueDynamic(GameMode, &AShootingGameModeBase::GameRestart);
	ButtonQuit->OnClicked.AddUniqueDynamic(GameMode, &AShootingGameModeBase::GameQuit);
}
