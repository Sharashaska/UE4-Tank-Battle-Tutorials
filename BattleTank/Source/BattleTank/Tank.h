// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//#include "TankAimingComponent.h" 
// ֻ�� header file �� include ��ĸ���, �����Ķ��� forward declaration. �� cpp file ���� include.
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();

protected:

private:
	
};
