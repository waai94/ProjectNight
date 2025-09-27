// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enum/StatsEnum.h"
#include "StatsItemBaseComponent.generated.h"

class UCharacterStats;
class AStatusItemBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class CPLUSFASTEST_API UStatsItemBaseComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UStatsItemBaseComponent();

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatsItem")
	StatsEnum statsType;// 変更するステータスの種類

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatsItem")
	FName statsName; // ステータスの名前
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatsItem")
	float valueToChangeStat; // キャラのステータスをどれだけ変化させるか　
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "StatsItem")
	void InitializeStatsItem(FName InStatsName, float InCurrentValue, float InMaxValue);

	UFUNCTION(BlueprintCallable, Category = "StatsItem")
	void PlayerTouchStatsItem(AActor* targetActor);// プレイヤーが触れたときの処理
		
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StatsItem")
	void OnStatsItemTouchedBP(AActor* targetActor);// Blueprintでの処理

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "StatsItem")
	FName GetStatsName() const { return statsName; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "StatsItem")
	float GetValueToChangeStat() const { return valueToChangeStat; }

	void ChangeCharacterStat(UCharacterStats* CharacterStats);

	
};
