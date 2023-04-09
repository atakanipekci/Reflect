// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectReflect/Activatables/RIActivatable.h"
#include "RLauncherPlatform.generated.h"

UCLASS()
class PROJECTREFLECT_API ARLauncherPlatform : public AActor, public IRActivatable
{
	GENERATED_BODY()
	
public:
	ARLauncherPlatform();
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex);

	virtual bool Activate() override;

	UPROPERTY()
	TArray<class ARCharacter*> CharactersToLaunch;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class URProjectileInteractorComponent* ProjectileInteractionComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LaunchVelocity = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool OverrideVelocityXY = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool OverrideVelocityZ = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ActivateOnOverlap;
};
