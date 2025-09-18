// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Bullet/BulletBase.h"
#include "Components/Bullet/BulletStatsComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABulletBase::ABulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BulletCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BulletCollision"));
	RootComponent = BulletCollision;
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(RootComponent);

	BulletStats = CreateDefaultSubobject<UBulletStatsComponent>(TEXT("BulletStats"));
	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovement"));
}

// Called when the game starts or when spawned
void ABulletBase::BeginPlay()
{
	Super::BeginPlay();
	BulletCollision->OnComponentHit.AddDynamic(this, &ABulletBase::HitTarget);//ターゲットにヒットイベントの紐づけ
	
}

// Called every frame
void ABulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABulletBase::InitializeBullet(const FVector& Direction)
{
	if (BulletStats && BulletMovement)
	{
		BulletMovement->Velocity = Direction * BulletStats->GetSpeed();
		BulletMovement->ProjectileGravityScale = BulletStats->GetGravityScale();
	}
}
void ABulletBase::HitTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("HitTarget"));
	if (BulletStats)
	{
		float finalDamage = BulletStats->GetBaseDamage();
		if (CheckHeadshot(Hit)) finalDamage *= BulletStats->GetHeadshotMultiplier();
		
			
		
		UGameplayStatics::ApplyDamage(OtherActor, finalDamage, nullptr, this, nullptr);
	}
	UE_LOG(LogTemp, Warning, TEXT("DamageApplied"));
	Destroy();
}

bool ABulletBase::CheckHeadshot(const FHitResult& Hit) const
{
	if (Hit.BoneName == FName("head") || Hit.BoneName == FName("Head") || Hit.BoneName == FName("HEAD"))
	{
		return true;
	}
	return false;
}

