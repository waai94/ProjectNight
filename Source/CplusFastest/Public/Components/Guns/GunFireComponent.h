// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GunFireComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),Blueprintable )
class CPLUSFASTEST_API UGunFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGunFireComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void StartFire();// Start firing the gun
	void StopFire();// Stop firing the gun

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
	void OnStartFireBP();//
	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
	void OnStopFireBP();//
};
