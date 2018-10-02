// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetControlledTank())
		return;

	// Where the crosshair hits
	FVector OutHitLocation;
	GetSightRayHitLocation(OutHitLocation);
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	// Get viewport size
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	// Get location of dot on screen (in pix)
	FVector2D ScreenLocation(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		if (GetLookVectorHitLocation(LookDirection, OutHitLocation))
		{
			return true;
		}
	}

	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector& LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult,
		PlayerCameraManager->GetCameraLocation(),
		PlayerCameraManager->GetCameraLocation() + LineTraceRange * LookDirection,
		ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}

	OutHitLocation = FVector(0.f, 0.f, 0.f);
	return false;
}

bool ATankPlayerController::GetLookDirection(const FVector2D& ScreenLocation, FVector & LookDirection) const
{
	// Deproject to world
	FVector CameraWorldLocation; // to be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y,
		CameraWorldLocation, LookDirection);
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* PossessedTank = GetControlledTank();
	
	if (!PossessedTank)
		UE_LOG(LogTemp, Error, TEXT("Player controller not possessing any tank"));
		
}


