// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BulletStatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPLUSFASTEST_API UBulletStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBulletStatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// ヘッダファイル内に記述
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage")
	float baseDamage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage")
	float damageDropPerMeter = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage")
	float minDamage = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage")
	float maxRange = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Projectile")
	float speed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Projectile")
	float gravityScale = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Projectile")
	float penetrationPower = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage")
	float headshotMultiplier = 2.f;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetBaseDamage() const { return baseDamage; };
	float GetDamageDropPerMeter() const { return damageDropPerMeter; };
	float GetMinDamage() const { return minDamage; };
	float GetMaxRange() const { return maxRange; };
	float GetSpeed() const { return speed; };
	float GetGravityScale() const { return gravityScale; };
	float GetPenetrationPower() const { return penetrationPower; };
	float GetHeadshotMultiplier() const { return headshotMultiplier; };

};
