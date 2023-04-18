// Fill out your copyright notice in the Description page of Project Settings.


#include "RPlayerAnimInstance.h"

void URPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	PlayerOwner = Cast<ARPlayerCharacter>(TryGetPawnOwner());
}

void URPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(PlayerOwner)
	{
		bIsFiring = PlayerOwner->GetIsFiring();
	}
}
