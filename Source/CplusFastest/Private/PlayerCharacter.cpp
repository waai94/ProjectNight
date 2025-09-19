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
	//CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->SetupAttachment(GetMesh(), FName("head"));
	CameraComponent->bUsePawnControlRotation = false;

	// ��̃R���W�����R���|�[�l���g�̍쐬
	handComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HandComponent"));
	handComponent->SetupAttachment(GetMesh(), FName("hand_r"));
	handComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// �X�e�[�^�X�R���|�[�l���g�̐����iHealthComp�͐e�ō쐬�ς݂Ȃ̂ŕs�v�j
	characterStats = CreateDefaultSubobject<UCharacterStats>(TEXT("CharacterStats"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (handComponent && GetMesh())
	{
		handComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("hand_r"));
	}

	// Enhanced Input Subsystem���擾����MappingContext��ǉ�
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	//�v���C���[���V�����ꍇ�̃C�x���g���o�C���h
	HealthComp->OnDeath.AddDynamic(this, &APlayerCharacter::OnPlayerDeath);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetFocusedActor();
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	// HealthComp�͐e�N���X�ŊǗ�
	if (HealthComp)
	{
		HealthComp->TakeDamage(ActualDamage);//�w���X�R���|�[�l���g�Ƀ_���[�W��`����
		UE_LOG(LogTemp, Warning, TEXT("Player took damage: %f"), ActualDamage);
	}
	return ActualDamage;
}

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

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void APlayerCharacter::OnPlayerDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Player has died."));
	GetMesh()->SetSimulatePhysics(true);
	OnDiedBP();
}

void APlayerCharacter::Fire(const FInputActionValue& Value)
{
	if (IsValid(CurrentGun))
	{
		CurrentGun->FireKeyPressed();
	}
}

void APlayerCharacter::SetCurrentGun(AGunBase* NewGun)
{
	CurrentGun = NewGun;
	if (IsValid(CurrentGun))
	{
		CurrentGun->AttachToComponent(handComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
		CurrentGun->SetOwner(this);
		UE_LOG(LogTemp, Warning, TEXT("Gun attached to hand."));
	}
}

void APlayerCharacter::OnDiedBP_Implementation()
{
	// Blueprint�Ŏ�������鎀�S�C�x���g
}

void APlayerCharacter::GetFocusedActor()
{
	FHitResult HitResult;
	FVector Start = CameraComponent->GetComponentLocation();
	FVector ForwardVector = CameraComponent->GetForwardVector();
	FVector End = ((ForwardVector * 200.f) + Start);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	bool bIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
	if (bIsHit)
	{
		AActor* FocusedActor = HitResult.GetActor();
		if (FocusedActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Focused Actor: %s"), *FocusedActor->GetName());
		}
	}
}