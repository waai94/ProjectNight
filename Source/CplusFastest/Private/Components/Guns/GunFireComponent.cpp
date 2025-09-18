// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Guns/GunFireComponent.h"

// Sets default values for this component's properties
UGunFireComponent::UGunFireComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGunFireComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGunFireComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
// Start firing the gun
void UGunFireComponent::StartFire()
{
	OnStartFireBP();
}
// Stop firing the gun
void UGunFireComponent::StopFire()
{
	OnStopFireBP();
}

void UGunFireComponent::OnStartFireBP_Implementation()
{
}

void UGunFireComponent::OnStopFireBP_Implementation()
{
}