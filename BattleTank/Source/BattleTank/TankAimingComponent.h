// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8 
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

// forward declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

// hold barrel's properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankAimingComponent();

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 6000.f; // 1000m/s

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = SetUp)
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	FText GetRoundsLeft() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category="State")
	EFiringState FiringState = EFiringState::Reloading;
	
private:
	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	double LastFireTime = 0;

	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 RoundsLeft = 10;

	UPROPERTY(EditDefaultsOnly, Category = "SetUp")
	float ReloadTimeInSeconds = 2.f;

	UPROPERTY(EditDefaultsOnly, Category = "SetUp")
	//UClass* ProjectileBlueprint;
	TSubclassOf<AProjectile> ProjectileBleuprint;

	void MoveBarrelTowards();

	bool IsBarrelMoving();
};
