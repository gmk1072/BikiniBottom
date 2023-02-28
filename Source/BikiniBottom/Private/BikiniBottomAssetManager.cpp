// Fill out your copyright notice in the Description page of Project Settings.


#include "BikiniBottomAssetManager.h"
#include "AbilitySystemGlobals.h"

void UBikiniBottomAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
