// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "RCharacter.h"
#include "RPlayerCharacter.generated.h"

UCLASS()
class PROJECTREFLECT_API ARPlayerCharacter : public ARCharacter
{
	GENERATED_BODY()
public:
	ARPlayerCharacter();
	
	virtual void AttachWeapon(class ARWeapon* Weapon, const FName& Socket) override;
	virtual void Death() override;
	virtual float GetTimeModifierMultiplier() const override {return 7.f;}
	virtual USkeletalMeshComponent* GetWeaponParentComponent() const override { return Mesh1P;}
	
	void AddDefaultMappingContext();
	void ShowTrajectory(bool show);
	void DebugShoot();

	bool GetIsFiring() const { return bIsAiming; }
	
	//TODO GET Rid of these
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);
	UFUNCTION(BlueprintCallable)
	void OnPossessed();
	//

private:	
	void AddFireMappingContext();

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,  meta = (AllowPrivateAccess = "true"))
	class URTimeManipulatorComponent* TimeManipulatorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* FireMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* FireReleasedAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* AlternateFireAction;

protected:
	
	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	class UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void GetSpawnPosAndRot(FVector& CamLoc, FRotator& CamRot) const;
	void Fire();
	void AlternateFire();
	void HoldFire();
	bool IsSpawnPositionValid();
	void TryUpdateTrajectoryComponent();

private:

	bool bIsAiming = false;
	float AimTimer = 0.f;
};
