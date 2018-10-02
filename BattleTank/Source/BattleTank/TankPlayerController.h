// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	// Crosshair location relative to the screen
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;

	// Line trace range
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;

	// Control the barrel to aim where the crosshair is
	void AimAtCrosshair();
	bool GetSightRayHitLocation(FVector&) const;
	bool GetLookDirection(const FVector2D&, FVector&) const;
	bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& OutHitLocation) const;

public:
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	ATank* GetControlledTank() const;
	
	
};
