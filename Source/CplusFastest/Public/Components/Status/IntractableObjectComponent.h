// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "IntractableObjectComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class CPLUSFASTEST_API UIntractableObjectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIntractableObjectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool bIsIntractable = true;// 相互作用可能かどうか

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IntractableObject", meta = (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> IntractableWidgetClass;

	UPROPERTY()
	UUserWidget* IntractableWidgetInstance;

	// オブジェクトの名前
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectInfo", meta = (AllowPrivateAccess = true))
	FString ObjectName = "default";

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsIntractable() const { return bIsIntractable; }

	UFUNCTION(BlueprintCallable)
	void SetIsIntractable(bool bNewIsIntractable) { bIsIntractable = bNewIsIntractable; }
		
	UFUNCTION(BlueprintCallable)
	void ShowIntractableWidget();

	UFUNCTION(BlueprintCallable)
	void HideIntractableWidget();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetObjectName() const { return ObjectName; }// オブジェクトの名前を取得

	UFUNCTION(BlueprintCallable,BlueprintPure)
	UUserWidget* GetIntractableWidgetInstance() const { return IntractableWidgetInstance; }
};
