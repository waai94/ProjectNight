// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StatusItemBase.generated.h"

class UCharacterStats;
class UStatsItemBaseComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatsItemTouched, AActor*, TouchedActor);
UCLASS()
class CPLUSFASTEST_API AStatusItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStatusItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnStatsItemTouched OnStatsItemTouched;// ステータスアイテムに触れたときのデリゲート
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
