// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Status/IntractableObjectComponent.h"
#include "Agents/MyAgentBase.h"
#include "Components/Status/AttachableComponent.h"
// Sets default values for this component's properties
UIntractableObjectComponent::UIntractableObjectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UIntractableObjectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if(IntractableWidgetClass)
	{
		IntractableWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), IntractableWidgetClass);
		if(IntractableWidgetInstance)
		{
		
		//	IntractableWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}


// Called every frame
void UIntractableObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
// 相互作用可能なウィジェットを表示
void UIntractableObjectComponent::ShowIntractableWidget()
{
	if(IntractableWidgetInstance&& !IntractableWidgetInstance->IsInViewport())
	{
		//IntractableWidgetInstance->SetVisibility(ESlateVisibility::Visible);
		IntractableWidgetInstance->AddToViewport();
		UE_LOG(LogTemp, Warning, TEXT("IntractableWidgetInstance added to viewport."));
	}
}
// 相互作用可能なウィジェットを非表示
void UIntractableObjectComponent::HideIntractableWidget()
{
	if(IntractableWidgetInstance&& IntractableWidgetInstance->IsInViewport())
	{
		IntractableWidgetInstance->RemoveFromParent();
	}
}

// 相互作用処理
void UIntractableObjectComponent::IntractStart(AActor* InteractingActor)
{
	if(!bIsIntractable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Object is not intractable."));
		return;
	}
	if(!InteractingActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("InteractingActor is null."));
		return;
	}
	AMyAgentBase* Agent = Cast<AMyAgentBase>(InteractingActor);
	if(!Agent)
	{
		UE_LOG(LogTemp, Warning, TEXT("InteractingActor is not of type AMyAgentBase."));
		return;
	}
	// ここに相互作用の具体的な処理を追加
	OnIntract(Agent);

	UAttachableComponent* AttachableComp = GetOwner()->FindComponentByClass<UAttachableComponent>();
	if(AttachableComp)
	{
		AttachableComp->AttachToAgent(Agent); // Agentにアタッチ
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No AttachableComponent found on the object."));
	}
}

void UIntractableObjectComponent::OnIntract_Implementation(AMyAgentBase* InteractingAgent)
{
	// Blueprintで実装される相互作用イベント
}