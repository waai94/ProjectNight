// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Status/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Applies damage to the actor, reducing current health
void UHealthComponent::TakeDamage(float DamageAmount)
{
	if(DamageAmount <= 0.0f || CurrentHealth <= 0.0f)
	{
		return; // No damage to apply or already dead
	}

	CurrentHealth -= DamageAmount;
	OnHealthChanged.Broadcast(CurrentHealth);// Broadcast health change event

	UE_LOG(LogTemp, Warning, TEXT("Compoent:Actor took damage: %f, Current Health: %f"), DamageAmount, CurrentHealth);
	if (CurrentHealth <= 0.0f)
	{
		CurrentHealth = 0.0f;
		OnDeath.Broadcast();// Broadcast death event
		UE_LOG(LogTemp, Warning, TEXT("Actor has died."));
	}
}
// Heals the actor by the specified amount
void UHealthComponent::Heal(float HealAmount)
{
	CurrentHealth += HealAmount;
	OnHealthChanged.Broadcast(CurrentHealth);// Broadcast health change event	
	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
		
	}
}

// Returns health as a percentage (0.0 to 1.0)
float UHealthComponent::GetHealthPercentage() const
{
	if (MaxHealth <= 0.0f)
	{
		return 0.0f;
	}
	return CurrentHealth / MaxHealth;
}

