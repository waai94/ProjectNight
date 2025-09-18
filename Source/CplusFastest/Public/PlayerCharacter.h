#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/Status/HealthComponent.h"
#include "Components/Status/CharacterStats.h"// CharacterStats�̃C���N���[�h
#include "PlayerCharacter.generated.h"


class AGunBase;
UCLASS(Blueprintable)
class CPLUSFASTEST_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Tick(float DeltaTime) override;
	// ���͊֐�
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Fire(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
	void OnDiedBP();// Blueprint�ł̎��S�C�x���g


	// �J�����R���|�[�l���g
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCameraComponent* CameraComponent;


public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	

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

	UPROPERTY(EditDefaultsOnly, Category = "InputMapping")
	class UInputAction* FireAction;

	UFUNCTION(Category = "Event")
		void OnPlayerDeath();

		UFUNCTION(BlueprintCallable, Category = "Weapon")
		void SetCurrentGun(AGunBase* NewGun);// ���݂̏e��ݒ�

		UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
		AGunBase* GetCurrentGun() const { return CurrentGun; }// ���݂̏e���擾

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* healthComponent;// HealthComponent

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCharacterStats* characterStats;// CharacterStats

		UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon")
		AGunBase* CurrentGun;// ���݂̏e

		void GetFocusedActor();// �������Ă���A�N�^�[���擾
};
