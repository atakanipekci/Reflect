// Fill out your copyright notice in the Description page of Project Settings.


#include "RWeapon.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
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
}

// Called when the game starts or when spawned
void ARWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARWeapon::AttachWeapon(ARPlayerCharacter* TargetCharacter)
{
	if(TargetCharacter)
	{
		AttachedCharacter = TargetCharacter;
		this->AttachToComponent(TargetCharacter->GetWeaponParentComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale, CharacterSocket);
		PlayerController = Cast<APlayerController>(AttachedCharacter->GetController());
		TargetCharacter->SetHasRifle(true);

		SetUpActionBindings();
	}
}

void ARWeapon::SetUpActionBindings()
{
	if(AttachedCharacter == nullptr)
	{
		return;
	}
	
	if (PlayerController)
	{
		if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ARWeapon::Fire);
		}
	}
}


