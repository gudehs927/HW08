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
	// pitch, yaw, roll ������ ȸ��
	// y��, x��, z�� ������ ȸ��

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
		ScaleSpeed *= -1.0f; // �ӵ� ����
	}

	if (!FMath::IsNearlyZero(ScaleSpeed))
	{
		Scale += ScaleSpeed * DeltaTime;
		SetActorScale3D(FVector(Scale));
	}
}

void AItem::ResetActorPosition() 
{
	SetActorLocation(FVector::ZeroVector); //��������
}

float AItem::GetRotationSpeed() const 
{
	return RotationSpeed;
}

// ������ - �޸𸮿� ����. �� �ѹ��� �����
// PostInitializeComponents - ������Ʈ�� �ϼ��� ���� ȣ��. ������Ʈ���� ������ �ְ�ޱ�, ��ȣ�ۿ�
// BeginPlay - ��ġ(Spawn) ����
// Tick(float DeltaTime) - �� ������ ���� ȣ���.
// Destroyed - ���� �Ǳ� ���� ȣ��ȴ�.
// EndPlay - ���� ���� , �ı� (Destroyed()), ���� ��ȯ