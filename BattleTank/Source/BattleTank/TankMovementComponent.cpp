// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!ensure(LeftTrack && RightTrack)) { return; }
	Throw = Throw * 0.5f;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	//UE_LOG(LogTemp, Warning, TEXT("%s %F"), *GetName(), Throw);
}

void UTankMovementComponent::Initialize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	
	float ForwardThrow = FVector::DotProduct(TankForwardDirection, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	FVector CrossProduct = FVector::CrossProduct(TankForwardDirection, AIForwardIntention);
	float RightThrow = CrossProduct.Z;
	IntendTurnRight(RightThrow);

	//UE_LOG(LogTemp, Warning, TEXT("%f   %f"), RightThrow, ForwardThrow);
}
