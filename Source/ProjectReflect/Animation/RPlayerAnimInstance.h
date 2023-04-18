// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ProjectReflect/Character/RPlayerCharacter.h"
#include "RPlayerAnimInstance.generated.h"

UENUM(BlueprintType)
enum class ERHandAnimType : uint8
{
	Beam UMETA(DisplayName="Beam"), 
	Projectile UMETA(DisplayName="Projectile"),
	Conjure UMETA(DisplayName="Conjure"),
	Lift UMETA(DisplayName="Lift"),
	PalmBlast UMETA(DisplayName="PalmBlast")
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTREFLECT_API URPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY()
	ARPlayerCharacter* PlayerOwner;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ERHandAnimType RightHandAnim = ERHandAnimType::PalmBlast;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ERHandAnimType LeftHandAnim = ERHandAnimType::Projectile;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsFiring = false;
};
