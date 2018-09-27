// Fill out your copyright notice in the Description page of Project Settings.

#include "AITankController.h"

void AAITankController::BeginPlay()
{
	Super::BeginPlay();

	ATank* PossessedTank = GetControlledTank();

	if (!PossessedTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AITankController not possessing tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AITankController possessing %s"), *PossessedTank->GetName());
	}
}

ATank * AAITankController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
