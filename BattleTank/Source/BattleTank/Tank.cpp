// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Classes/Engine/World.h"
#include "TankTrack.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("MovementComponent"));

}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent,
	class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) {
		OnDeath.Broadcast();
	}

	//UE_LOG(LogTemp, Warning, TEXT("DamageApplied: %i. DamageAmount: %f. Health: %i."), DamageToApply, DamageAmount, CurrentHealth);
	return 0.0f;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}
