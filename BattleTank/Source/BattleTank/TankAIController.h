// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = Setup)
	float AcceptanceRadius = 5000.f;

private:
	
};
