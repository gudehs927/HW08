// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h" //generated.�ش� ������ �ݵ�� �������� ��ġ�ؾ� ��


UCLASS()
class SPARTAPROJECT_API AItem : public AActor // ���ξ� A�� Actor Ŭ������ ��ӹ޴´ٴ� ���� ��Ÿ��
{
	GENERATED_BODY()

public:
	AItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Components") // ���� �ȵ�
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components") // ���� �ΰ��� ����
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="Item|Properties") //���� �ϳ��� ����
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
