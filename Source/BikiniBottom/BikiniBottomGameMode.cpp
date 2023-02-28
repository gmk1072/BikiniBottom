// Copyright Epic Games, Inc. All Rights Reserved.

#include "BikiniBottomGameMode.h"
#include "BikiniBottomCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABikiniBottomGameMode::ABikiniBottomGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
