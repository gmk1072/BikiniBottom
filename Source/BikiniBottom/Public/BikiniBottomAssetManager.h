// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "BikiniBottomAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class BIKINIBOTTOM_API UBikiniBottomAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	virtual void StartInitialLoading() override;
};
