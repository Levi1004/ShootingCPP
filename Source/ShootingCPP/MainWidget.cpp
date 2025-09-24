// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Components/TextBlock.h"
void UMainWidget::PrintScore(int32 CurrentScore)
{
	ScoreData->SetText(FText::AsNumber(CurrentScore));
}
