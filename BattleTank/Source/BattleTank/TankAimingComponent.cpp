// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringState = EFiringState::Aiming;
	}
	else {
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!Barrel) { return; }

	auto BarrelLocation = Barrel->GetComponentLocation();
	
	//calculate out velocity
	FVector OutLaunchVelocity(0.f);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	TArray <AActor *> ActorsToIgnore;
	
	bool Result = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	auto Time = GetWorld()->GetTimeSeconds();
	if (Result) {
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards();

		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s."), *(GetOwner()->GetName()), *(HitLocation.ToString()), *(BarrelLocation.ToString()));
	}
}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (!BarrelToSet || !TurretToSet) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards()
{
	if (!Barrel || !Turret) { return; }
	// get barrel rotation
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch); 

	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else // Avoid going the long-way round
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForwardVector = Barrel->GetForwardVector();
	bool bIsBarrelMoving = BarrelForwardVector.Equals(AimDirection, 0.01f);
	return !bIsBarrelMoving;
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringState::Reloading) {
		if (!ensure(Barrel && ProjectileBleuprint)) { return; }
		//spawn a projectile at the socket location
		FVector SocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator SocketRotation = Barrel->GetSocketRotation(FName("Projectile"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBleuprint, SocketLocation, SocketRotation);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
