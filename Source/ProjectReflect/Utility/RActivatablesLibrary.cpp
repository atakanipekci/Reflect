// Fill out your copyright notice in the Description page of Project Settings.


#include "RActivatablesLibrary.h"

#include "ProjectReflect/Activatables/RIActivatable.h"

bool URActivatablesLibrary::ActivateAllComponents(AActor* Actor, bool bDeactivate /* = false*/)
{
	if(Actor == nullptr)
	{
		return false;
	}

	for (auto Component : Actor->GetComponents())
	{
		if(IRActivatable* ActivatableComponent = Cast<IRActivatable>(Component))
		{
			if(bDeactivate)
			{
				ActivatableComponent->IDeactivate();
			}
			else
			{
				ActivatableComponent->IActivate();
			}
		}
	}

	return true;
}
