// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeYaw)
{
	float CurrentYaw = RelativeRotation.Yaw;
	float RotationSign = FMath::Sign(RelativeYaw);

	// Rotate at maximum speed
	float YawChange = RotationSign * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	float NewYaw = CurrentYaw + YawChange;

	// To avoid flickering. TODO implement a better control to avoid this
	if (FMath::Abs(RelativeYaw) > AnglePrecision)
		SetRelativeRotation(FRotator(0.f, NewYaw, 0.f));
}



