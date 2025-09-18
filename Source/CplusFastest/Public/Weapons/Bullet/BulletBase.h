// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BulletBase.generated.h"

class UBulletStatsComponent;

UCLASS()
class CPLUSFASTEST_API ABulletBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet")
	UStaticMeshComponent* BulletMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet")
	USphereComponent* BulletCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet")
	UProjectileMovementComponent* BulletMovement;

	UFUNCTION()//AddDynamic�ɂ�UFUNCTION���K�{
	void HitTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);//�^�[�Q�b�g�Ƀq�b�g

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet")
	UBulletStatsComponent* BulletStats;


	bool CheckHeadshot(const FHitResult& Hit) const;//�w�b�h�V���b�g���ǂ����`�F�b�N

	void InitializeBullet(const FVector& Direction);//�e�̏�����
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

};
