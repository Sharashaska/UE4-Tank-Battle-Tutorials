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
	Locked
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
	// Sets default values for this component's properties
	UTankAimingComponent();

public:	
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 6000.f; // 1000m/s

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = SetUp)
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category="State")
	EFiringState FiringState = EFiringState::Aiming;
	
private:
	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "SetUp")
	//UClass* ProjectileBlueprint;
	TSubclassOf<AProjectile> ProjectileBleuprint;

	UPROPERTY(EditDefaultsOnly, Category = "SetUp")
	float ReloadTimeInSeconds = 3.f;

	double LastFireTime = 0;	

};
