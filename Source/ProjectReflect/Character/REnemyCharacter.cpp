// Fill out your copyright notice in the Description page of Project Settings.


#include "REnemyCharacter.h"

#include "ProjectReflect/Weapon/RWeapon.h"

void AREnemyCharacter::FireWeapon(AActor* Target /* = nullptr*/)
{
	if(AttachedWeapon && !AttachedWeapon->IsShootCooldownActive())
	{
		PlayCharacterFireAnimation();

		FRotator SpawnRotation = GetActorRotation();
		if(Target)
		{
			SpawnRotation = (Target->GetActorLocation()-GetActorLocation()).Rotation();
		}
		const auto SpawnLocation = GetActorLocation() + GetActorForwardVector()*100;
		
		AttachedWeapon->Shoot(SpawnLocation, SpawnRotation);
	}
}
