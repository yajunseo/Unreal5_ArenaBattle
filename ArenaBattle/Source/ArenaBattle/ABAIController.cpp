// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AABAIController::AABAIController()
{
	//RepeatInterval = 3.0f;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Script/AIModule.BlackboardData'/Game/AI/BB_ABCharacter.BB_ABCharacter'"));
	if(BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_ABCharacter.BT_ABCharacter'"));
	if(BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AABAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//etWorld()->GetTimerManager().SetTimer(ReapeatTimerHandle, this, &AABAIController::OnRepeatTimer, RepeatInterval, true);
	
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if(UseBlackboard(BBAsset, BlackboardComp))
	{
		if(!RunBehaviorTree(BTAsset))
		{
			
		}
	}
}

// void AABAIController::OnUnPossess()
// {
// 	Super::OnUnPossess();
// 	GetWorld()->GetTimerManager().ClearTimer(ReapeatTimerHandle);
// }
//
// void AABAIController::OnRepeatTimer()
// {
// 	auto CurrentPawn = GetPawn();
// 	ABCHECK(CurrentPawn != nullptr);
//
// 	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
// 	if(NavSystem == nullptr)
// 		return;
//
// 	FNavLocation NextLocation;
// 	if(NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation))
// 	{
// 		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation);
// 	}
// }
