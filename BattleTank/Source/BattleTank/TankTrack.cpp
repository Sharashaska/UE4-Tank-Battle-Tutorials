// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankTrack::ApplySidewayForce()
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();

	// calculate the slippage speed
	// DotProduct 的参数前后顺序不重要
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// work out the acquired acceleration this frame to correct
	auto CorrectAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// calculate and apply sideway friction (F = m a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto TankMass = TankRoot->GetMass();
	auto CorrectionForce = TankMass * CorrectAcceleration / 2; // 2 tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	// Ben 教的版本
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	// 同学提供的版本
	//auto ForceApplied = GetForwardVector() * FMath::Clamp<float>(Throttle, -0.5f, 0.5f) * TrackMaxDrivingForce;

	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit) {
	// 这个方法每个 tick 都会被调用一次

	// drive the track
	DriveTrack();
	// apply sideway force
	ApplySidewayForce();
	// reset throttle
	CurrentThrottle = 0.f;
}
