// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RIActivatable.h"
#include "GameFramework/Actor.h"
#include "RDoor.generated.h"

UCLASS()
class PROJECTREFLECT_API ARDoor : public AActor, public IRActivatable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual bool IActivate() override;
	virtual bool IDeactivate() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class URMovingPlatformComponent* MovingPlatformComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMeshComponent;
};
