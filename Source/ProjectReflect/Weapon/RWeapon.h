// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RWeapon.generated.h"

UCLASS()
class PROJECTREFLECT_API ARWeapon : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	USceneComponent* Root;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY()
	float ShootCooldownCounter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta=(AllowPrivateAccess = "true"))
	float ShootCooldown;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	FName MuzzleSocket = "Muzzle";

	// Sets default values for this actor's properties
	ARWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void Shoot(FVector Location, FRotator Rotation);

	bool IsShootCooldownActive() const;

	UFUNCTION()
	virtual void SecondaryFire() {/*Empty cause optional*/}
};

