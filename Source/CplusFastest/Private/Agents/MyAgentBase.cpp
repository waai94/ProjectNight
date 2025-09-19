// Fill out your copyright notice in the Description page of Project Settings.


#include "Agents/MyAgentBase.h"
#include "Components/Status/HealthComponent.h"

// Sets default values
AMyAgentBase::AMyAgentBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ヘルスコンポーネント生成
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
}

// Called when the game starts or when spawned
void AMyAgentBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(HealthComp))
	{
		HealthComp->OnDeath.AddDynamic(this, &AMyAgentBase::OnAgentDeath);
		UE_LOG(LogTemp, Log, TEXT("Health Component is valid and event bound."));
	}
}

float AMyAgentBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage <= 0.f)
	{
		return 0.f;
	}
	if (IsValid(HealthComp))
	{
		HealthComp->TakeDamage(ActualDamage);
		UE_LOG(LogTemp, Log, TEXT("Agent took damage: %f, Current Health: %f"), ActualDamage, HealthComp->GetCurrentHealth());
	}
	return ActualDamage;
}
void AMyAgentBase::OnAgentDeath()
{
	// 死亡処理
	GetMesh()->SetSimulatePhysics(true);//メッシュに物理シミュレーションを適用
	UE_LOG(LogTemp, Warning, TEXT("Agent has died."));
}

void AMyAgentBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input


