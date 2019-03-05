// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
//#include "Engine/World.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank()) {
		//aim the the player
		FVector PlayerTankLocation = GetPlayerTank()->GetActorLocation();
		GetControlledTank()->AimAt(PlayerTankLocation);

		//move toward the player

		//fire if ready

	}
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn) {
		ATank* PlayerTank = Cast<ATank>(PlayerPawn);
		//UE_LOG(LogTemp, Warning, TEXT("Player Controller possessing %s."), *(PlayerTank->GetName()));
		return PlayerTank;
	}
	return nullptr;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	GetPlayerTank();
	/*
	auto Tank = GetControlledTank();
	if (Tank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller possessing %s."), *(Tank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller not possessed!"));
	}
	*/
}
