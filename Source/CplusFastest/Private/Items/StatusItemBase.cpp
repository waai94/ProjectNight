// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/StatusItemBase.h"
#include "Components/BoxComponent.h"
#include "Components/Status/StatsItemBaseComponent.h"


// Sets default values
AStatusItemBase::AStatusItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);// 衝突判定用コンポーネントをシーンコンポーネントにアタッチ

}

// Called when the game starts or when spawned
void AStatusItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (CollisionComponent)
	{
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AStatusItemBase::OnOverlapBegin);// 衝突判定用コンポーネントのオーバーラップイベントをバインド
	}
}

// Called every frame
void AStatusItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// 何かと衝突したときに呼ばれる関数
void AStatusItemBase::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		OnStatsItemTouched.Broadcast(OtherActor);
	}
}
