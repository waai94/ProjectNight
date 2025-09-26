// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsItemBaseComponent.generated.h"

class UCharacterStats;
class AStatusItemBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPLUSFASTEST_API UStatsItemBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsItemBaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	enum StatsEnum //変更するステータス
	{
		defence, // 防御力
		movementSpeed, // 移動速度
		accuracy, // 命中率
		throwPower, // 投擲力 追加予定
		health, // 体力 追加予定
		shield, // シールド 追加予定
		jump, // 追加予定
		additionalEffects // 追加効果 追加予定

	};

	StatsEnum statsType;// 変更するステータスの種類
	FName statsName; // ステータスの名前
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
