#include "NewPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


ANewPlayerCharacter::ANewPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// SpringArm作成
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 300.f;
	SpringArmComponent->bUsePawnControlRotation = true;

	// カメラ作成
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	//ステータスコンポーネントの生成
	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));// HealthComponentの作成
	//characterStats = CreateDefaultSubobject<UCharacterStats>(TEXT("CharacterStats"));// CharacterStatsの作成
}

void ANewPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Enhanced Input Subsystemを取得してMappingContextを追加
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
// ダメージ処理
float ANewPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ensure(healthComponent != nullptr);
	if (healthComponent)
	{
		healthComponent->TakeDamage(ActualDamage);// HealthComponentにダメージを適用
	}
	return ActualDamage;
}
// 入力バインド
void ANewPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANewPlayerCharacter::Move);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANewPlayerCharacter::Look);

	}
}
// 移動処理
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
// 視点操作
void ANewPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void ANewPlayerCharacter::OnPlayerDeath()
{
	// プレイヤーキャラクターの死亡処理をここに実装
	// 例: アニメーションの再生、ゲームオーバー画面の表示など
	UE_LOG(LogTemp, Warning, TEXT("Player has died."));

	//キャラクターのラグドール化
	GetMesh()->SetSimulatePhysics(true);
}