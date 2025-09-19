#pragma once

#include "CoreMinimal.h"
#include "Agents/MyAgentBase.h" // 親クラスを変更
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/Status/HealthComponent.h"
#include "Components/Status/CharacterStats.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.generated.h"

class AGunBase;
UCLASS(Blueprintable)
class CPLUSFASTEST_API APlayerCharacter : public AMyAgentBase // 継承元を変更
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Tick(float DeltaTime) override;

	// 入力関数
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Fire(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
	void OnDiedBP();

	// カメラコンポーネント
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USphereComponent* handComponent;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// SpringArmでカメラを追従させる
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComponent;

	// Input Mapping
	UPROPERTY(EditDefaultsOnly, Category = "InputMapping")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "InputMapping")
	class UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "InputMapping")
	class UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "InputMapping")
	class UInputAction* FireAction;

	UFUNCTION(Category = "Event")
	void OnPlayerDeath();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetCurrentGun(AGunBase* NewGun);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	AGunBase* GetCurrentGun() const { return CurrentGun; }

protected:
	// 親クラスで HealthComp を既に持つため、healthComponent → HealthComp を利用
	// ここでは再定義せず characterStats のみ保持
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCharacterStats* characterStats;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon")
	AGunBase* CurrentGun;

	void GetFocusedActor();
};