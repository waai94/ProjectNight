// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Status/StatsItemBaseComponent.h"
#include "Components/Status/CharacterStats.h"


// Sets default values for this component's properties
UStatsItemBaseComponent::UStatsItemBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatsItemBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatsItemBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UStatsItemBaseComponent::InitializeStatsItem(FName InStatsName, float InCurrentValue, float InMaxValue)
{
}

void UStatsItemBaseComponent::PlayerTouchStatsItem(AActor* targetActor)
{
	// プレイヤーが触れたときの処理
	if (!targetActor) return;// targetActorがnullptrの場合は処理を中断
	ChangeCharacterStat(targetActor->FindComponentByClass<UCharacterStats>());// キャラクターのステータスを変更

	OnStatsItemTouchedBP(targetActor);
}

void UStatsItemBaseComponent::OnStatsItemTouchedBP_Implementation(AActor* targetActor)
{
}

// キャラクターのステータスを変更
void UStatsItemBaseComponent::ChangeCharacterStat(UCharacterStats* CharacterStats)
{
	if (!CharacterStats) return;
	switch (statsType)
	{
	case defence:
	{
		float NewDefence = CharacterStats->GetCurrentDefence() + valueToChangeStat;
		CharacterStats->SetCurrentDefence(NewDefence);
		break;
	}
	case movementSpeed:
	{
		float NewMovementSpeed = CharacterStats->GetCurrentMovementSpeed() + valueToChangeStat;
		CharacterStats->SetCurrentMovementSpeed(NewMovementSpeed);
		break;
	}
	case accuracy:
	{
		float NewAccuracy = CharacterStats->GetCurrentAccuracy() + valueToChangeStat;
		CharacterStats->SetCurrentAccuracy(NewAccuracy);
		break;
	}
	case throwPower:
	{
		// 投擲力の処理を追加予定
		break;
	}
	case health:
	{
		// 体力の処理を追加予定
		break;
	}
	case shield:
	{
		// シールドの処理を追加予定
		break;
	}
	case jump:
	{
		// ジャンプの処理を追加予定
		break;
	}
	case additionalEffects:
	{
		// 追加効果の処理を追加予定
		break;
	}
	default:
		break;
	}
}