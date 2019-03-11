// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//#include "TankAimingComponent.h" 
// ֻ�� header file �� include ��ĸ���, �����Ķ��� forward declaration. �� cpp file ���� include.
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;
class UTankMovementComponent;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 6000.f; // 1000m/s

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = "SetUp")
	//UClass* ProjectileBlueprint;
	TSubclassOf<AProjectile> ProjectileBleuprint;

	UPROPERTY(EditDefaultsOnly, Category = "SetUp")
	float ReloadTimeInSeconds = 3.f;
	
	double LastFireTime = 0;

	UTankBarrel* Barrel = nullptr; // TODO remove

	virtual void BeginPlay() override;
};
