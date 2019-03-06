// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
//#include "Engine/World.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank* ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank) {
		//aim the the player
		FVector PlayerTankLocation = PlayerTank->GetActorLocation();
		ControlledTank->AimAt(PlayerTankLocation);

		//move toward the player

		//fire every frame
		ControlledTank->Fire();
	}
}

/*ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}*/

/*ATank * ATankAIController::GetPlayerTank() const
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn) {
		ATank* PlayerTank = Cast<ATank>(PlayerPawn);
		//UE_LOG(LogTemp, Warning, TEXT("Player Controller possessing %s."), *(PlayerTank->GetName()));
		return PlayerTank;
	}
	return nullptr;
}*/

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}
