// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PawnPlayer.generated.h"



UCLASS()
class SHOOTINGCPP_API APawnPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// EditAnywhere는 해당 속성을 엔진 어디서든 수정할 수 있게 해준다.
	// class 클래스 이름 : 전방선언
	// 전방선언을 하면 뒤에 온 이름을 클래스 타입이라고 가정하고 진해안다.
	// 전방선언을 사용하는게 코드가 유연해진다. 
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;
	
	// VisibleAnywhere는 해당 속성을 엔진에서 어디서든 읽을 수 있게 해준다.
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
	class UInputMappingContext* IMC_PlayerInput;

	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Horizontal;

	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Vertical;

	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Fire;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* FirePosition;

	// TSubclassOf : <>에 넣은 클래스와 그 자식 클래스를 넣을 수 있는 타입. / 템플릿 
	// ABullet 클래스와 자식 클래스가 들어갈 수 있다면.
	// BP_Bullet도 들어갈 수 있다.
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> BulletFactory;

	UPROPERTY(EditAnywhere)
	class USoundBase* fireSound;

    UPROPERTY(EditAnywhere)
	float MoveSpeed = 500.0f;


private:
	float HorizontalValue;
	float VerticalValue;


private:
	// 이 함수를 IA_Horizontal에 바인딩을 시켜서 
	// 키 입력 -> IA_Horizontal -1f, 1f 반환 -> OnInputHorizontal가 실행
	// const struct FInputActionvalue& Value 매개변수에 입력값이 들어온다.
	void OnInputHorizontal(const struct FInputActionValue& Value);
	void OnInputVertical(const struct FInputActionValue& Value);
	void Fire();
};
