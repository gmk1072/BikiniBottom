// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class BikiniBottomAbilityID : uint8
{
	None UMETA(DispayName = "None"),
	Confirm UMETA(DispayName = "Confirm"),
	Cancel UMETA(DispayName = "Cancel"),
};