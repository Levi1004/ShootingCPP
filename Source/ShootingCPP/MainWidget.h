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
	// BindWidget : 이 붙은 변수는 쟝ㅎㄷㅅ 블루프린트에서 반드시 widget에 포함시켜야된다.
	// BindWidget 키워드가 붙은 변수가 widget에 생성이 됐는지 확인하는건 
	// ScoreText 처럼 이름으로 매칭을 시키기떄문에, widget 블루프린트에서 이름을 일치시켜야 된다.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ScoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ScoreData;

public:
	UFUNCTION()
	void PrintScore(int32 CurrentScore);

	
};
