// Fill out your copyright notice in the Description page of Project Settings.

#include "AITankController.h"
#include "../Public/AITankController.h"
#include "Engine/World.h"

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
		ATank* PlayerTank = GetPlayerTank();
		if (!PlayerTank)
		{
			UE_LOG(LogTemp, Error, TEXT("Cannot find player tank from %s"), *PossessedTank->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s sees player tank is %s"), *PossessedTank->GetName(), *PlayerTank->GetName());
		}
	}

	
}

void AAITankController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	GetControlledTank()->AimAt(GetPlayerTank()->GetTargetLocation());
}

ATank * AAITankController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * AAITankController::GetPlayerTank() const
{
	ATank* PlayerTank = nullptr;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find player controller from AI Tank"));
	}
	else
	{
		PlayerTank = Cast<ATank>(PlayerController->GetPawn());
	}

	return PlayerTank;
}
