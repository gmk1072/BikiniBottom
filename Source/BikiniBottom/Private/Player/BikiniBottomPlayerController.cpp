// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BikiniBottomPlayerController.h"
#include "Player/BikiniBottomPlayerState.h"
#include "AbilitySystemComponent.h"

void ABikiniBottomPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABikiniBottomPlayerState* PS = GetPlayerState<ABikiniBottomPlayerState>();
	if (PS)
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PlayerState, InPawn);
	}
}

//TODO -- Add HUD Stuff
