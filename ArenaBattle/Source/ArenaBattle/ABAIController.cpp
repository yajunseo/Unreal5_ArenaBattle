// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAIController.h"

#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AABAIController::AABAIController()
{
	RepeatInterval = 3.0f;
}

void AABAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	GetWorld()->GetTimerManager().SetTimer(ReapeatTimerHandle, this, &AABAIController::OnRepeatTimer, RepeatInterval, true);
}

void AABAIController::OnUnPossess()
{
	Super::OnUnPossess();
	GetWorld()->GetTimerManager().ClearTimer(ReapeatTimerHandle);
}

void AABAIController::OnRepeatTimer()
{
	auto CurrentPawn = GetPawn();
	ABCHECK(CurrentPawn != nullptr);

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if(NavSystem == nullptr)
		return;

	FNavLocation NextLocation;
	if(NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation);
	}
}
