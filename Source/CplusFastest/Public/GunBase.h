// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

class UGunFireComponent;
UCLASS()
class CPLUSFASTEST_API AGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunBase();

	UGunFireComponent* GunFireComponent;//銃の発射コンポーネント
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireKeyPressed();//発射ボタンを押したとき

	void FireKeyReleased();//発射ボタンを離したとき
};
