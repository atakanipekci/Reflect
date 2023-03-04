// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "RWeaponComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTREFLECT_API URWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
	URWeaponComponent();
	
	void SpawnProjectile() const;
	void PlayCharacterFireAnimation() const;

	UPROPERTY()
	class ARPlayerCharacter* Character;

protected:
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	virtual void BeginPlay() override;

	UPROPERTY()
	UWorld* World;
	
public:
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ARProjectile> ProjectileClass;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	// USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(class ARPlayerCharacter* TargetCharacter);

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();
	void SetUpActionBindings();
};

