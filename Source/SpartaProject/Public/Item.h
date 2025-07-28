// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h" //generated.해더 파일은 반드시 마지막에 위치해야 함


UCLASS()
class SPARTAPROJECT_API AItem : public AActor // 접두어 A는 Actor 클래스를 상속받는다는 것을 나타냄
{
	GENERATED_BODY()

public:
	AItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Components") // 수정 안됨
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components") // 수정 두개다 가능
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="Item|Properties") //수정 하나만 가능
	float RotationSpeed;
	float SpeedZ;
	float OfSet;
	float SinZ;
	float Scale;
	float PlusTime;
	float ScaleSize;
	float MaxScale;
	float MinScale;
	float ScaleSpeed;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Item|Actions")
	void ResetActorPosition();

	UFUNCTION(BlueprintPure, Category = "Item|Properties")
	float GetRotationSpeed() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Item|Event")
	void OnItemPickedUp();
};
