// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyAgentBase.generated.h"

class UHealthComponent;
class UItemDropComponent;
UCLASS()
class CPLUSFASTEST_API AMyAgentBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyAgentBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* HealthComp;//ヘルスコンポーネント

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UItemDropComponent* ItemDropComp;// アイテムドロップコンポーネント

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	int teamID = 0;// チームID

	UFUNCTION()
	void OnAgentDeath();// 死亡処理
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input

	UFUNCTION(BlueprintCallable,BlueprintPure)
	int GetTeamID() const { return teamID; }

	UFUNCTION(BlueprintCallable)
	void SetTeamID(int NewTeamID) { teamID = NewTeamID; }
};
