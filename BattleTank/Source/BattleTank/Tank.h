// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
// ֻ�� header file �� include ��ĸ���, �����Ķ��� forward declaration. �� cpp file ���� include.
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator, AActor * DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health") // a const blueprint method
	float GetHealthPercent() const; // return current health. value between 0 and 1

	FTankDelegate OnDeath;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 1000;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;

};
