#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GunBase.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// SpringArm�쐬
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 300.f;
	SpringArmComponent->bUsePawnControlRotation = true;

	// �J�����쐬
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(GetMesh(), FName("head"));//�J���������b�V����headSocket�ɃA�^�b�`
	CameraComponent->bUsePawnControlRotation = false;//�J�������R���g���[���[�̉�]���g�p���Ȃ��悤�ɐݒ�

	//�X�e�[�^�X�R���|�[�l���g�̐���
	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));// HealthComponent�̍쐬
	characterStats = CreateDefaultSubobject<UCharacterStats>(TEXT("CharacterStats"));// CharacterStats�̍쐬
}

void APlayerCharacter::BeginPlay()
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
			healthComponent->OnDeath.AddDynamic(this, &APlayerCharacter::OnPlayerDeath);
		}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// �������Ă���A�N�^�[���擾
	GetFocusedActor();
}
// �_���[�W����
float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInput->BindAction(FireAction, ETriggerEvent::Started, this, &APlayerCharacter::Fire);

	}
}
// �ړ�����
void APlayerCharacter::Move(const FInputActionValue& Value)
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
void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
	UE_LOG(LogTemp, Warning, TEXT("LookVector X: %f, Y: %f"), LookVector.X, LookVector.Y);
}

void APlayerCharacter::OnPlayerDeath()
{
	// �v���C���[�L�����N�^�[�̎��S�����������Ɏ���
	// ��: �A�j���[�V�����̍Đ��A�Q�[���I�[�o�[��ʂ̕\���Ȃ�
	UE_LOG(LogTemp, Warning, TEXT("Player has died."));

	//�L�����N�^�[�̃��O�h�[����
	GetMesh()->SetSimulatePhysics(true);
	OnDiedBP();
	
}

void APlayerCharacter::Fire(const FInputActionValue& Value)
{
	if (IsValid(CurrentGun))
	{
		CurrentGun->FireKeyPressed();//�e�̔��ˊ֐����Ăяo��
	}
	
}

void APlayerCharacter::SetCurrentGun(AGunBase* NewGun)
{
	CurrentGun = NewGun;
}

void APlayerCharacter::OnDiedBP_Implementation()
{
	// Blueprint�Ŏ�������鎀�S�C�x���g
}

// �������Ă���A�N�^�[���擾
void APlayerCharacter::GetFocusedActor()
{
	FHitResult HitResult;// �q�b�g���ʂ��i�[����ϐ�
	FVector Start = CameraComponent->GetComponentLocation();// �J�����̈ʒu���擾
	FVector ForwardVector = CameraComponent->GetForwardVector();// �J�����̑O���x�N�g�����擾
	FVector End = ((ForwardVector * 200.f) + Start);// ���C�̒�����200�ɐݒ�
	FCollisionQueryParams CollisionParams;// �Փ˃N�G���p�����[�^�̐ݒ�
	CollisionParams.AddIgnoredActor(this);
	bool bIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);// ���C�L���X�g�̎��s
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);// �f�o�b�O���C���̕`��
	if (bIsHit)
	{
		AActor* FocusedActor = HitResult.GetActor();
		if (FocusedActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Focused Actor: %s"), *FocusedActor->GetName());
		}
	}
}