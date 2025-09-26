// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStats.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPLUSFASTEST_API UCharacterStats : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStats();

    // Defence
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats")
    float GetCurrentDefence() const { return currentDefence; }

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetCurrentDefence(float Value) { currentDefence = FMath::Clamp(Value, 0.f, maxDefence); }

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats")
    float GetMaxDefence() const { return maxDefence; }

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetMaxDefence(float Value) { maxDefence = Value; }

    // Movement Speed
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats")
    float GetCurrentMovementSpeed() const { return currentMovementSpeed; }

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetCurrentMovementSpeed(float Value) { currentMovementSpeed = FMath::Clamp(Value, 0.f, maxMovementSpeed); }

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats")
    float GetMaxMovementSpeed() const { return maxMovementSpeed; }

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetMaxMovementSpeed(float Value) { maxMovementSpeed = Value; }

    // Accuracy
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats")
    float GetCurrentAccuracy() const { return currentAccuracy; }

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetCurrentAccuracy(float Value) { currentAccuracy = FMath::Clamp(Value, 0.f, maxAccuracy); }

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats")
    float GetMaxAccuracy() const { return maxAccuracy; }

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetMaxAccuracy(float Value) { maxAccuracy = Value; }

    // Throw Power
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats")
    float GetCurrentThrowPower() const { return currentThrowPower; }

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetCurrentThrowPower(float Value) { currentThrowPower = FMath::Clamp(Value, 0.f, maxThrowPower); }

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats")
    float GetMaxThrowPower() const { return maxThrowPower; }

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetMaxThrowPower(float Value) { maxThrowPower = Value; }

    // Jump Power
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats")
    float GetCurrentJumpPower() const { return currentJumpPower; }

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetCurrentJumpPower(float Value) { currentJumpPower = FMath::Clamp(Value, 0.f, maxJumpPower); }

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats")
    float GetMaxJumpPower() const { return maxJumpPower; }

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetMaxJumpPower(float Value) { maxJumpPower = Value; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float currentDefence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float maxDefence = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float currentMovementSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float maxMovementSpeed = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float currentAccuracy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float maxAccuracy = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float currentThrowPower;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float maxThrowPower = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float currentJumpPower;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float maxJumpPower = 1000.f;
}; 
