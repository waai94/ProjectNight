// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "GunBase.generated.h"

class UGunFireComponent;
UCLASS()
class CPLUSFASTEST_API AGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunBase();

	UGunFireComponent* GunFireComponent;//�e�̔��˃R���|�[�l���g

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun")
	USceneComponent* Root;//���[�g�R���|�[�l���g
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun")
	USkeletalMeshComponent* GunMesh;//�e�̃��b�V��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun")
	UArrowComponent* MuzzleLocation;//�e���̈ʒu

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireKeyPressed();//���˃{�^�����������Ƃ�

	void FireKeyReleased();//���˃{�^���𗣂����Ƃ�
};
