#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

// 修正ポイント：デリゲートの型名を一致させた
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, CurrentHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPLUSFASTEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// コンストラクタ
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// 修正ポイント：型指定を明示
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentHealth = 100.f;

public:
	// Tickは不要なのでfalseにする場合はコメント
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 修正ポイント：正しいデリゲート型を指定
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;

	// Health操作関数
	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float DamageAmount);
	// Heal関数の引数名を修正
	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(float HealAmount);
	// Health取得関数
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	float GetHealthPercentage() const;
	// CurrentHealthとMaxHealthのゲッターを追加
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	float GetCurrentHealth() const { return CurrentHealth; }
	// 修正ポイント：MaxHealthのゲッターを追加
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	float GetMaxHealth() const { return MaxHealth; }
};
