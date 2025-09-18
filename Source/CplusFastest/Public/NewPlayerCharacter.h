#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/Status/HealthComponent.h"
//#include "Components/Status/CharacterStats.h"// CharacterStats�̃C���N���[�h
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
	// ���͊֐�
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// �J�����R���|�[�l���g
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;

	// SpringArm�ŃJ������Ǐ]������
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
