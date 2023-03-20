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

	ARPlayerCharacter();
	
	void AttachDefaultWeapon();

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapon, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AActor> DefaultWeaponBP;

	UPROPERTY()
	class ARWeapon* AttachedWeapon;

protected:
	
	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	class UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem;
	
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;
	
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	void HideTrajectory() const;
	void ShowTrajectory() const;

	USkeletalMeshComponent* GetWeaponParentComponent() const;
};
