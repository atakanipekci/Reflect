// Fill out your copyright notice in the Description page of Project Settings.


#include "RTimeManager.h"

#include "RITimeModifiable.h"
#include "Kismet/GameplayStatics.h"

RTimeManager::RTimeManager()
{
}

RTimeManager::~RTimeManager()
{
}

void RTimeManager::ModifyTime(UWorld* World, float Modifier, bool bIgnoreCustomMultipliers /* = false*/)
{
	if(World == nullptr)
	{
		return;
	}
	
	TArray<AActor*> TimeModifiables;
	UGameplayStatics::GetAllActorsWithInterface(World,URTimeModifiable::StaticClass(),TimeModifiables);

	for (const auto TimeModifiable : TimeModifiables)
	{
		if(TimeModifiable == nullptr)
		{
			continue;
		}

		if(bIgnoreCustomMultipliers == false)
		{
			IRTimeModifiable* AsTimeModifiable = Cast<IRTimeModifiable>(TimeModifiable);
			if(AsTimeModifiable)
			{
				TimeModifiable->CustomTimeDilation = Modifier * AsTimeModifiable->GetTimeModifierMultiplier();
			}
		}
		else
		{
			TimeModifiable->CustomTimeDilation = Modifier;
		}
	}
}
