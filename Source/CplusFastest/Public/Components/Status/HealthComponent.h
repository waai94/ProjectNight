#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

// �C���|�C���g�F�f���Q�[�g�̌^������v������
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, CurrentHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPLUSFASTEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// �R���X�g���N�^
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// �C���|�C���g�F�^�w��𖾎�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentHealth = 100.f;

public:
	// Tick�͕s�v�Ȃ̂�false�ɂ���ꍇ�̓R�����g
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// �C���|�C���g�F�������f���Q�[�g�^���w��
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;

	// Health����֐�
	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float DamageAmount);
	// Heal�֐��̈��������C��
	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(float HealAmount);
	// Health�擾�֐�
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	float GetHealthPercentage() const;
	// CurrentHealth��MaxHealth�̃Q�b�^�[��ǉ�
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	float GetCurrentHealth() const { return CurrentHealth; }
	// �C���|�C���g�FMaxHealth�̃Q�b�^�[��ǉ�
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	float GetMaxHealth() const { return MaxHealth; }
};
