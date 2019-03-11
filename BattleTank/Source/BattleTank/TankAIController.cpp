// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
//#include "Engine/World.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank* ControlledTank = Cast<ATank>(GetPawn());

	if (!ensure(PlayerTank)) { return; }

	//aim the the player
	FVector PlayerTankLocation = PlayerTank->GetActorLocation();
	ControlledTank->AimAt(PlayerTankLocation);

	//move toward the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	//fire every frame
	ControlledTank->Fire();
	
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}


