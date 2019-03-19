// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }

	//aim the the player
	FVector PlayerTankLocation = PlayerTank->GetActorLocation();
	auto TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)) { return;  }
	TankAimingComponent->AimAt(PlayerTankLocation);

	//fire every frame
	if (TankAimingComponent->GetFiringState() == EFiringState::Locked) {
		TankAimingComponent->Fire();
	}

	//move toward the player
	MoveToActor(PlayerTank, AcceptanceRadius);

}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}


