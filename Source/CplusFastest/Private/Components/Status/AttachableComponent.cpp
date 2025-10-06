// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Status/AttachableComponent.h"
#include "Agents/MyAgentBase.h"
// Sets default values for this component's properties
UAttachableComponent::UAttachableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttachableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttachableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAttachableComponent::AttachToAgent(AMyAgentBase* targetAgent)// Agent
{
	if(bCanAttach && targetAgent)
	{
		FAttachmentTransformRules attachRules(EAttachmentRule::SnapToTarget, true);
		this->GetOwner()->AttachToComponent(targetAgent->GetMesh(), attachRules, FName("Head")); // Attach to the agent's head socket
		bCanAttach = false;
		OnAttachToAgentBP(targetAgent);
	}
}

void UAttachableComponent::OnAttachToAgentBP_Implementation(AMyAgentBase* targetAgent)// Blueprint
{
}