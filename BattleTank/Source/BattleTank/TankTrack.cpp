// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	// Ben 教的版本
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	
	// 同学提供的版本
	//auto ForceApplied = GetForwardVector() * FMath::Clamp<float>(Throttle, -0.5f, 0.5f) * TrackMaxDrivingForce;
	
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	//UE_LOG(LogTemp, Warning, TEXT("%s %F"), *GetName(), Throttle);
}
