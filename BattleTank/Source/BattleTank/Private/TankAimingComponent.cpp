// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


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

	//UE_LOG(LogTemp, Warning, TEXT("%s aiming from %s to %s"), *GetOwner()->GetName(), *StartLocation.ToString(), *HitLocation.ToString());

	if (AimIsGood)
	{
		FVector AimDirection = OutLaunchSpeed.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());
	}
}

void UTankAimingComponent::SetBarrel(UStaticMeshComponent * BarrelToSet)
{
	Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

