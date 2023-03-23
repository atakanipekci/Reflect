// Fill out your copyright notice in the Description page of Project Settings.


#include "RCharacter.h"

#include "ProjectReflect/Weapon/RWeapon.h"

// Sets default values
ARCharacter::ARCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LifeComponent = CreateDefaultSubobject<URLifeComponent>(TEXT("Life Component"));
}

float ARCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                              AActor* DamageCauser)
{
	if(LifeComponent == nullptr)
	{
		return 0.f;
	}

	return LifeComponent->TakeDamage(DamageAmount,DamageEvent, EventInstigator, DamageCauser);
}

void ARCharacter::Death()
{
	Destroy();
}

// Called when the game starts or when spawned
void ARCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(LifeComponent)
	{
		LifeComponent->HealthReachedZero.AddUObject(this, &ARCharacter::Death);
	}

	AttachDefaultWeapon();
}

// Called every frame
void ARCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARCharacter::PlayCharacterFireAnimation() const
{
	if(AnimInstance)
	{
		AnimInstance->Montage_Play(FireAnimation, 1.f);
	}
}

void ARCharacter::AttachWeapon(ARWeapon* Weapon, const FName& Socket)
{
	if(Weapon)
	{
		Weapon->AttachToComponent(GetWeaponParentComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
	}
}

void ARCharacter::AttachDefaultWeapon()
{
	if(DefaultWeaponBP)
	{
		const auto SpawnedWeapon = GetWorld()->SpawnActor<ARWeapon>(DefaultWeaponBP, GetActorTransform());
		AttachWeapon(SpawnedWeapon, MainWeaponSocket);
	}
}

