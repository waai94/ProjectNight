// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Status/IntractableObjectComponent.h"

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
