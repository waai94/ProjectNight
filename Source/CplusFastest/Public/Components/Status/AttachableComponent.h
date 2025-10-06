// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttachableComponent.generated.h"

class AMyAgentBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPLUSFASTEST_API UAttachableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttachableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool bCanAttach = true;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Attachable")
	void AttachToAgent(AMyAgentBase* targetAgent);// Agent

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Attachable")
	void OnAttachToAgentBP(AMyAgentBase* targetAgent);// Blueprint

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "Attachable")
	bool GetCanAttach() const { return bCanAttach; }// Get whether it can be attached

	UFUNCTION(BlueprintCallable, Category = "Attachable")
	void SetCanAttach(bool bNewCanAttach) { bCanAttach = bNewCanAttach; }// Set whether it can be attached
};
