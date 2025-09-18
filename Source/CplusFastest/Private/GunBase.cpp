// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"
#include "Components/Guns/GunFireComponent.h"
// Sets default values
AGunBase::AGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();

	GunFireComponent = FindComponentByClass<UGunFireComponent>();//銃の発射コンポーネントを取得
	
}

// Called every frame
void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunBase::FireKeyPressed()//発射ボタンを押したとき
{
	if(GunFireComponent)
	{
		GunFireComponent->StartFire();//銃の発射コンポーネントの発射開始関数を呼び出す
	}
}

void AGunBase::FireKeyReleased()//発射ボタンを離したとき
{
	if(GunFireComponent)
	{
		GunFireComponent->StopFire();//銃の発射コンポーネントの発射停止関数を呼び出す
	}

}