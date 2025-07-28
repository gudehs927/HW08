#include "Item.h"

AItem::AItem()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Chair.SM_Chair"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Metal_Gold.M_Metal_Gold"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 90.0f;
	SpeedZ = 5.0f;
	OfSet = 200.0f;
	SinZ = 100.0f;
	Scale = 2.0f;
	PlusTime = 0.0f;
	ScaleSize = 10.0f;
	MaxScale = 5.0f;
	MinScale = 1.0f;
	ScaleSpeed = 1.0f;

}



void AItem::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(300.0f, 200.0f, 100.0f));
	SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
	SetActorScale3D(FVector(2.0f));
	// pitch, yaw, roll 순서로 회전
	// y축, x축, z축 순서로 회전

	OnItemPickedUp();
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlusTime += DeltaTime;

	if(!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f ));
	}
	if (!FMath::IsNearlyZero(SpeedZ))
	{
		SetActorLocation(FVector(0.0f, 0.0f, SinZ *FMath::Sin(PlusTime * SpeedZ)+OfSet));
	}
	if (Scale >= MaxScale || Scale <= MinScale)
	{
		ScaleSpeed *= -1.0f; // 속도 반전
	}

	if (!FMath::IsNearlyZero(ScaleSpeed))
	{
		Scale += ScaleSpeed * DeltaTime;
		SetActorScale3D(FVector(Scale));
	}
}

void AItem::ResetActorPosition() 
{
	SetActorLocation(FVector::ZeroVector); //원점으로
}

float AItem::GetRotationSpeed() const 
{
	return RotationSpeed;
}

// 생성자 - 메모리에 생김. 딱 한번만 실행됨
// PostInitializeComponents - 컴포넌트가 완성된 직후 호출. 컴포넌트끼리 데이터 주고받기, 상호작용
// BeginPlay - 배치(Spawn) 직후
// Tick(float DeltaTime) - 매 프레임 마다 호출됨.
// Destroyed - 삭제 되기 직전 호출된다.
// EndPlay - 게임 종료 , 파괴 (Destroyed()), 레벨 전환