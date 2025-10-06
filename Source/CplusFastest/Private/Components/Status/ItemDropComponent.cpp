// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Status/ItemDropComponent.h"

// Sets default values for this component's properties
UItemDropComponent::UItemDropComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemDropComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UItemDropComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UItemDropComponent::DropItems()
{
	if (ItemDropList.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemDropList is empty."));
		return;
	}
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemDropComponent has no owner."));
		return;
	}
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to get World context."));
		return;
	}
	FVector SpawnLocation = Owner->GetActorLocation();
	FRotator SpawnRotation = FRotator::ZeroRotator;
	for (const FItemDropInfo& ItemInfo : ItemDropList)
	{
		if (!ItemInfo.ItemClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid ItemClass in ItemDropList."));
			continue;
		}
		int32 RandomChance = FMath::RandRange(1, 100);
		if (RandomChance <= ItemInfo.DropChance)
		{
			FActorSpawnParameters SpawnParams;
			AActor* SpawnedItem = World->SpawnActor<AActor>(ItemInfo.ItemClass, SpawnLocation, SpawnRotation, SpawnParams); ///アイテムのスポーン
			if (SpawnedItem)
			{
				UE_LOG(LogTemp, Log, TEXT("Dropped item: %s"), *SpawnedItem->GetName());//アイテムのスポーンに成功した場合のログ
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to spawn item of class: %s"), *ItemInfo.ItemClass->GetName());
			}
		}
	}
}

