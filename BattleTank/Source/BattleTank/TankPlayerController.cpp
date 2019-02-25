// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GetControlledTank();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	ATank* Tank = Cast<ATank>(GetPawn());
	if (Tank) {
		UE_LOG(LogTemp, Warning, TEXT("Controlled tank is %s."), *(Tank->GetName()));
	}
	return Tank;
}