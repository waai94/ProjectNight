// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemDropComponent.generated.h"



USTRUCT(BlueprintType)
struct FItemDropInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDrop")
	TSubclassOf<AActor> ItemClass; // The class of the item to drop

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDrop")
	int32 DropChance; // The chance (percentage) of this item dropping
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPLUSFASTEST_API UItemDropComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemDropComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDrop")
	TArray<FItemDropInfo> ItemDropList;// List of items with their drop chances

	UFUNCTION(BlueprintCallable, Category = "ItemDrop")
	void DropItems();// Function to drop items based on the drop chances
};
