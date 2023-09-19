// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

const FName AABAIController::HomePosKey(TEXT("HomePos"));
const FName AABAIController::PatrolPosKey(TEXT("PatrolPos"));

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

	ABLOG(Warning, TEXT("%d"), 1);
	
	ABLOG(Warning, TEXT("%d"), 2);

	if(UseBlackboard(BBAsset, BlackboardComp))
	{
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		
		ABLOG(Warning, TEXT("%d"), 3);
		if(!RunBehaviorTree(BTAsset))
		{
			ABLOG(Warning, TEXT("%d"), 4);
		}
	}
	
	ABLOG(Warning, TEXT("%d"), 5);
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
