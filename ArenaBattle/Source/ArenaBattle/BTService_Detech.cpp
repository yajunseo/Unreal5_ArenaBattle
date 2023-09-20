// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detech.h"

#include "ABAIController.h"
#include "ABCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_Detech::UBTService_Detech()
{
	NodeName = TEXT("Detech");
	Interval = 1.0f;
}

void UBTService_Detech::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(ControllingPawn == nullptr) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 600.0f;

	if(World == nullptr) return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, ECC_EngineTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius), CollisionQueryParam);

	if(bResult)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AABAIController::TargetKey, nullptr);
		
		for (auto const& OverlapResult : OverlapResults)
		{
			AABCharacter* ABCharacter = Cast<AABCharacter>(OverlapResult.GetActor());
			if(ABCharacter && ABCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AABAIController::TargetKey, ABCharacter);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(World, ABCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), ABCharacter->GetActorLocation(), FColor::Blue, false, 0.2f);
				return;
			}
		}
	}
}
