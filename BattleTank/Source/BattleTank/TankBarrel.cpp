// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// calculate elevation change needed for this frame
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	auto ElevationChange = RelativeSpeed * MaxDegreePerSecond * (GetWorld()->DeltaTimeSeconds);

	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto NewElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegree, MaxElevationDegree);

	SetRelativeRotation(FRotator(NewElevation, 0.f, 0.f));
	
	// rotate barrel by tick

	// given a max elevation speed, and the frame time

	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: Elevating at %f."), Time, RelativeSpeed);
}

