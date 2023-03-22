// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RWeapon.generated.h"

UCLASS()
class PROJECTREFLECT_API ARWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void Fire(FVector Location, FRotator Rotation) PURE_VIRTUAL(Fire,);

	UFUNCTION()
	virtual void SecondaryFire() {/*Empty cause optional*/}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	FName MuzzleSocket = "Muzzle";

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMesh;

private:
	UPROPERTY()
	USceneComponent* Root;

};
