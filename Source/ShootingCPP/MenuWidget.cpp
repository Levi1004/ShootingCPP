// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Components/Button.h"
#include "ShootingGamemodeBase.h"

void UMenuWidget::AddListener(AShootingGamemodeBase* GameMode)
{
    ButtonRestart->OnClicked.AddUniqueDynamic(GameMode, &AShootingGamemodeBase::GameRestart);
	ButtonQuit->OnClicked.AddUniqueDynamic(GameMode, &AShootingGamemodeBase::GameQuit);
}
