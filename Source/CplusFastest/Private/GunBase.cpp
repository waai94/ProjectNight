// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"
#include "Components/Guns/GunFireComponent.h"
// Sets default values
AGunBase::AGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));//���[�g�R���|�[�l���g���쐬
	RootComponent = Root;//���[�g�R���|�[�l���g�����[�g�ɐݒ�
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));//�e�̃��b�V���R���|�[�l���g���쐬
	GunMesh->SetupAttachment(Root);//�e�̃��b�V���R���|�[�l���g�����[�g�ɐڑ�
	MuzzleLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("MuzzleLocation"));//�e���̈ʒu�R���|�[�l���g���쐬
	MuzzleLocation->SetupAttachment(RootComponent);//�e���̈ʒu�R���|�[�l���g���e�̃��b�V���R���|�[�l���g�ɐڑ�
}

// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();

	GunFireComponent = FindComponentByClass<UGunFireComponent>();//�e�̔��˃R���|�[�l���g���擾
	
}

// Called every frame
void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunBase::FireKeyPressed()//���˃{�^�����������Ƃ�
{
	if(GunFireComponent)
	{
		GunFireComponent->StartFire();//�e�̔��˃R���|�[�l���g�̔��ˊJ�n�֐����Ăяo��
	}
}

void AGunBase::FireKeyReleased()//���˃{�^���𗣂����Ƃ�
{
	if(GunFireComponent)
	{
		GunFireComponent->StopFire();//�e�̔��˃R���|�[�l���g�̔��˒�~�֐����Ăяo��
	}

}