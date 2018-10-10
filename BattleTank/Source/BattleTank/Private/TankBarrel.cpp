// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

void UTankBarrel::Elevate(float RelativePitch)
{
	float RotationSign = FMath::Sign(RelativePitch);

	// Account for frame time dilation
	auto ElevationChange = RotationSign * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	// Clamping
	RawNewElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	// Avoid flickering: TODO implement a better control to avoid this
	if (FMath::Abs(RelativePitch) > AnglePrecision)
		SetRelativeRotation(FRotator(RawNewElevation, 0, 0));
}


