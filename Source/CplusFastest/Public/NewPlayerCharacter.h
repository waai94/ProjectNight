#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/Status/HealthComponent.h"
//#include "Components/Status/CharacterStats.h"// CharacterStatsのインクルード
#include "NewPlayerCharacter.generated.h"



UCLASS(Blueprintable)
class CPLUSFASTEST_API ANewPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANewPlayerCharacter();

protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	// 入力関数
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// カメラコンポーネント
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;

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

	UFUNCTION(Category = "Event")
	void OnPlayerDeath();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* healthComponent;// HealthComponent

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
//	UCharacterStats* characterStats;// CharacterStats
};
