// Fill out your copyright notice in the Description page of Project Settings.


#include "RWeapon.h"
#include "ProjectReflect/Character/RPlayerCharacter.h"

// Sets default values
ARWeapon::ARWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(RootComponent);
	
	ShootCooldownCounter = ShootCooldown;
}

// Called when the game starts or when spawned
void ARWeapon::BeginPlay()
{
	Super::BeginPlay();
}

bool ARWeapon::IsShootCooldownActive() const
{
	return ShootCooldownCounter < ShootCooldown;
}

// Called every frame
void ARWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(ShootCooldownCounter < ShootCooldown)
	{
		ShootCooldownCounter += DeltaTime;
		ShootCooldownCounter = FMath::Min(ShootCooldownCounter, ShootCooldown);
	}
}

void ARWeapon::Shoot(FVector Location, FRotator Rotation)
{
	ShootCooldownCounter = 0;
}
