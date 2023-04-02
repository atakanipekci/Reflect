// Fill out your copyright notice in the Description page of Project Settings.

#include "RPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "ProjectReflect/Components/RProjectileTrajectoryComponent.h"
#include "ProjectReflect/Weapon/RProjectileWeapon.h"
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

void ARPlayerCharacter::OnPossessed()
{
	PlayerController = Cast<APlayerController>(Controller);
	if(PlayerController)
	{
		EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		AddDefaultMappingContext();
		if(bHasRifle)
		{
			AddFireMappingContext();
		}
	}
}

void ARPlayerCharacter::BeginPlay()
{
	AnimInstance = Mesh1P->GetAnimInstance();
	PlayerController = Cast<APlayerController>(Controller);
	if(PlayerController)
	{
		EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		AddDefaultMappingContext();
	}
	
	Super::BeginPlay();
}

void ARPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TryUpdateTrajectoryComponent();
}

void ARPlayerCharacter::AddFireMappingContext()
{
	if (PlayerController && EnhancedInputSubsystem)
	{
		// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
		if(!EnhancedInputSubsystem->HasMappingContext(FireMappingContext))
		{
			EnhancedInputSubsystem->AddMappingContext(FireMappingContext, 1);	
		}
	}
}

void ARPlayerCharacter::AddDefaultMappingContext()
{
	if(PlayerController && EnhancedInputSubsystem)
	{
		if(!EnhancedInputSubsystem->HasMappingContext(FireMappingContext))
		{
			EnhancedInputSubsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ARPlayerCharacter::AttachWeapon(ARWeapon* Weapon, const FName& Socket)
{
	if(Weapon)
	{
		Super::AttachWeapon(Weapon, Socket);
		SetHasRifle(true);

		//TODO remove mapping context on weapon detach
		AddFireMappingContext();
	}
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

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ARPlayerCharacter::Fire);
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

void ARPlayerCharacter::GetSpawnPosAndRot(FVector& CamLoc, FRotator& CamRot) const
{
	if(PlayerController == nullptr) return;
	PlayerController->GetPlayerViewPoint(CamLoc, CamRot);
	CamLoc = CamLoc + CamRot.Vector().GetSafeNormal() * 100;
}

void ARPlayerCharacter::Fire()
{
	if(!IsSpawnPositionValid()) return;
	
	if(AttachedWeapon && !AttachedWeapon->IsShootCooldownActive())
	{
		PlayCharacterFireAnimation();
		if(PlayerController && PlayerController->PlayerCameraManager)
		{
			FVector SpawnLoc;
			FRotator SpawnRot;
			GetSpawnPosAndRot(SpawnLoc, SpawnRot);
			AttachedWeapon->Shoot(SpawnLoc, SpawnRot);
		}
	}
}

bool ARPlayerCharacter::IsSpawnPositionValid()
{
	if(FirstPersonCameraComponent == nullptr) return false;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(AttachedWeapon);
	
	FHitResult Hit;
	FVector TraceStart = FirstPersonCameraComponent->GetComponentLocation();
	FVector TraceEnd;
	FRotator SpawnRot;

	GetSpawnPosAndRot(TraceEnd, SpawnRot);

	FVector ExtraDist = (TraceEnd - TraceStart).GetSafeNormal() * 50;
	TraceEnd = TraceEnd + ExtraDist;

	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_GameTraceChannel1, QueryParams);

	// DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Red : FColor::Green, false, 0.2f, 0, 3.0f);

	return Hit.GetActor() == nullptr;
}

void ARPlayerCharacter::TryUpdateTrajectoryComponent()
{
	if(AttachedWeapon == nullptr) return;

	const auto ProjectileWeapon = Cast<ARProjectileWeapon>(AttachedWeapon);

	if(ProjectileWeapon == nullptr) return;
	if(ProjectileWeapon->TrajectoryComponent == nullptr) return;
	if(!ProjectileWeapon->TrajectoryComponent->IsTrajectoryActive()) return;

	if(!IsSpawnPositionValid())
	{
		ProjectileWeapon->TrajectoryComponent->ClearTrajectory();
		return;
	}
	
	FVector SpawnPos;
	FRotator SpawnRot;
	GetSpawnPosAndRot(SpawnPos, SpawnRot);
	
	TArray<TObjectPtr<AActor>> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	ActorsToIgnore.Add(ProjectileWeapon);
	
	ProjectileWeapon->DrawTrajectory(SpawnPos, SpawnRot.Vector(), ActorsToIgnore);

	/** If there is no dynamic object on the map that can collide with the projectile, you can optimize this to
	 only update when player moves themselves or moves their aim*/
}

void ARPlayerCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

void ARPlayerCharacter::ShowTrajectory(bool show)
{
	if(AttachedWeapon == nullptr) return;

	const auto ProjectileWeapon = Cast<ARProjectileWeapon>(AttachedWeapon);

	if(ProjectileWeapon == nullptr) return;

	if(ProjectileWeapon->TrajectoryComponent)
	{
		if(show)
		{
			ProjectileWeapon->TrajectoryComponent->SpawnTrajectorySpline();
		}
		else
		{
			ProjectileWeapon->TrajectoryComponent->DestroyTrajectory();
		}
	}
}

void ARPlayerCharacter::DebugShoot()
{
	Fire();
}
