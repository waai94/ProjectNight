#include "NewPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


ANewPlayerCharacter::ANewPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// SpringArm�쐬
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 300.f;
	SpringArmComponent->bUsePawnControlRotation = true;

	// �J�����쐬
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	//�X�e�[�^�X�R���|�[�l���g�̐���
	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));// HealthComponent�̍쐬
	//characterStats = CreateDefaultSubobject<UCharacterStats>(TEXT("CharacterStats"));// CharacterStats�̍쐬
}

void ANewPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Enhanced Input Subsystem���擾����MappingContext��ǉ�
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}

	}
	//healthComponent = FindComponentByClass<UHealthComponent>();
	if (IsValid(healthComponent))
	{
		healthComponent->OnDeath.AddDynamic(this, &ANewPlayerCharacter::OnPlayerDeath);
	}
}
// �_���[�W����
float ANewPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ensure(healthComponent != nullptr);
	if (healthComponent)
	{
		healthComponent->TakeDamage(ActualDamage);// HealthComponent�Ƀ_���[�W��K�p
	}
	return ActualDamage;
}
// ���̓o�C���h
void ANewPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANewPlayerCharacter::Move);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANewPlayerCharacter::Look);

	}
}
// �ړ�����
void ANewPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Forward, MovementVector.Y);
		AddMovementInput(Right, MovementVector.X);
	}
}
// ���_����
void ANewPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void ANewPlayerCharacter::OnPlayerDeath()
{
	// �v���C���[�L�����N�^�[�̎��S�����������Ɏ���
	// ��: �A�j���[�V�����̍Đ��A�Q�[���I�[�o�[��ʂ̕\���Ȃ�
	UE_LOG(LogTemp, Warning, TEXT("Player has died."));

	//�L�����N�^�[�̃��O�h�[����
	GetMesh()->SetSimulatePhysics(true);
}