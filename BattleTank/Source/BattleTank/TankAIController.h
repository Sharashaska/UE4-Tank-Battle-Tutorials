// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
//#include "Tank.h"
//#include "Engine/World.h"
//#include "GameFramework/PlayerController.h"
#include "TankAIController.generated.h"

class ATank;
//class UWorld;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float AcceptanceRadius = 3000.f;
};
