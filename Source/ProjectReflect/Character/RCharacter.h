// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProjectReflect/Components/RLifeComponent.h"
#include "ProjectReflect/TimeModify/RITimeModifiable.h"
#include "RCharacter.generated.h"

UCLASS()
class PROJECTREFLECT_API ARCharacter : public ACharacter, public IRTimeModifiable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void Death();
	
	void PlayCharacterFireAnimation() const;

	virtual void AttachWeapon(class ARWeapon* Weapon, const FName& Socket);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void AttachDefaultWeapon();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Gameplay, meta=(AllowPrivateAccess = "true"))
	FName MainWeaponSocket = "GripPoint";

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapon, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AActor> DefaultWeaponBP;
	
	virtual USkeletalMeshComponent* GetWeaponParentComponent() const { return GetMesh();}
	
protected:

	UPROPERTY()
	UAnimInstance* AnimInstance;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	URLifeComponent* LifeComponent;

	UPROPERTY()
	ARWeapon* AttachedWeapon;
};
