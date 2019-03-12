// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrossHair();
}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!ensure(GetPawn())) {
		return;
	}
	
	FVector HitLocation; // out parameter
	if (GetSightRayHitLocation(HitLocation)) {
		//get world location through crosshair

		//if hit something, then control tank to aim at this point
		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		if (!ensure(AimingComponent)) { return; }
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	//deproject the screen position of crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction is %s."), *LookDirection.ToString());

		//line trace along that look direction, see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector CameraWorldLocation;
	bool Result = DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
	return Result;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation(); /********/
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	bool Result = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	);

	if (Result) {
		//set HitLocation
		HitLocation = HitResult.Location;
		//UE_LOG(LogTemp, Warning, TEXT("Hit Result is %s."), *(HitResult.Actor->GetName()));
	}
	else {
		HitLocation = FVector(0.f);
	}
	//UE_LOG(LogTemp, Warning, TEXT("Hit Location is %s."), *(HitLocation.ToString()));
	return Result;
}


