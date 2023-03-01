// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BikiniBottomPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BIKINIBOTTOM_API ABikiniBottomPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
