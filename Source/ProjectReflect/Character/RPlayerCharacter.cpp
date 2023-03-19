// Fill out your copyright notice in the Description page of Project Settings.

#include "RPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "ProjectReflect/Weapon/RWeapon.h"

// Sets default values
ARPlayerCharacter::ARPlayerCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

// Called when the game starts or when spawned
void ARPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = Mesh1P->GetAnimInstance();
	PlayerController = Cast<APlayerController>(Controller);
	EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	EnhancedInputSubsystem->AddMappingContext(DefaultMappingContext, 0);

	AttachDefaultWeapon();
}

void ARPlayerCharacter::AttachDefaultWeapon()
{
	if(DefaultWeaponBP)
	{
		const auto Weapon = GetWorld()->SpawnActor<ARWeapon>(DefaultWeaponBP, GetActorTransform());
		Weapon->AttachWeapon(this);
		//const auto WeaponComponent = Cast<URWeaponComponent>(Weapon->GetComponentByClass(URWeaponComponent::StaticClass()));
		//WeaponComponent->AttachWeapon(this);
	}
}
USkeletalMeshComponent* ARPlayerCharacter::GetWeaponParentComponent() const
{
	return Mesh1P;
}

void ARPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARPlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARPlayerCharacter::Look);
	}
}

void ARPlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	auto const MovementVector  = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ARPlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	auto const LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ARPlayerCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

