// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// calculate elevation change needed for this frame
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	auto RotationChange = RelativeSpeed * MaxDegreePerSecond * (GetWorld()->DeltaTimeSeconds);
	auto Rotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0.f, Rotation, 0.f));

	//UE_LOG(LogTemp, Warning, TEXT("%s."), *RelativeRotation.ToString());
}

