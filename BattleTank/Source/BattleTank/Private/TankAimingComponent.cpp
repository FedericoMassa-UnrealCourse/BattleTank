// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Compute difference of rotation that the barrel needs to do
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	
	// Decide what direction it is easier to rotate the turret
	// If rotation is > 180 it means that it would be easier rotating the other way
	if (FMath::Abs(DeltaRotator.Yaw) > 180)
		DeltaRotator.Yaw -= 360 * FMath::Sign(DeltaRotator.Yaw);

	Turret->Rotate(DeltaRotator.Yaw);
}

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimAt(const FVector & HitLocation, const float& LaunchSpeed)
{
	if (!GetOwner())
	{
		UE_LOG(LogTemp, Error, TEXT("Aiming component has no owner"));
		return;
	}

	// Check if barrel was set on Tank blueprint
	if (!Barrel)
	{
		UE_LOG(LogTemp, Error, TEXT("Barrel not defined in TankAimingComponent"));
		return;
	}

	// Check if barrel was set on Tank blueprint
	if (!Turret)
	{
		UE_LOG(LogTemp, Error, TEXT("Turret not defined in TankAimingComponent"));
		return;
	}

	auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector OutLaunchSpeed;

	bool AimIsGood = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchSpeed,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0F,
		0.0F,
		ESuggestProjVelocityTraceOption::DoNotTrace);

	if (AimIsGood)
	{
		FVector AimDirection = OutLaunchSpeed.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::SetBarrel(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurret(UTankTurret * TurretToSet)
{
	Turret = TurretToSet;
}