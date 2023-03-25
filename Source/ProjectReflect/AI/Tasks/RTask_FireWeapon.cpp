// Fill out your copyright notice in the Description page of Project Settings.


#include "RTask_FireWeapon.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "ProjectReflect/AI/RAIController.h"
#include "ProjectReflect/Character/REnemyCharacter.h"

EBTNodeResult::Type URTask_FireWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ARAIController* const Controller = Cast<ARAIController>(OwnerComp.GetAIOwner());
	AREnemyCharacter* Character = Cast<AREnemyCharacter>(Controller->GetPawn());
	if(Controller && Character)
	{
		if(Controller->GetBlackboardComponent())
		{
			AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
			Character->FireWeapon(Target);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}
