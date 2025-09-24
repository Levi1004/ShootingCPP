// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// BindWidget : �� ���� ������ �������� �������Ʈ���� �ݵ�� widget�� ���Խ��Ѿߵȴ�.
	// BindWidget Ű���尡 ���� ������ widget�� ������ �ƴ��� Ȯ���ϴ°� 
	// ScoreText ó�� �̸����� ��Ī�� ��Ű�⋚����, widget �������Ʈ���� �̸��� ��ġ���Ѿ� �ȴ�.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ScoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ScoreData;

public:
	UFUNCTION()
	void PrintScore(int32 CurrentScore);

	
};
