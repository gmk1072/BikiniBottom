// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "Character/Abilities/AttributesSets/CharacterAttributeSetBase.h"
#include "GameplayEffectTypes.h"
#include "BikiniBottomPlayerState.generated.h"
/**
 * 
 */
UCLASS()
class BIKINIBOTTOM_API ABikiniBottomPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ABikiniBottomPlayerState();

	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	class UCharacterAttributeSetBase* GetAttributeSetBase() const;

	UFUNCTION(BlueprintCallable, Category = "BikiniBottom|BikiniBottomPlayerState")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "BikiniBottom|BikiniBottomPlayerState|UI")
	void ShowAbilityConfirmCancelText(bool ShowText);

	UFUNCTION(BlueprintCallable, Category = "BikiniBottom|BikiniBottomPlayerState|Attributes")
	int32 GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable, Category = "BikiniBottom|BikiniBottomPlayerState|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "BikiniBottom|BikiniBottomPlayerState|Attributes")
	float GetMaxHealth() const;

protected:
	UPROPERTY()
	class UCharacterAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY()
	class UCharacterAttributeSetBase* AttributeSetBase;

	FGameplayTag DeadTag;

	FDelegateHandle CharacterLevelChangedDelegateHandle;
	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;

	virtual void BeginPlay() override;

	virtual void CharacterLevelChanged(const FOnAttributeChangeData& Data);
	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);

	virtual void StunTagChanged(const FGameplayTag CallbaackTag, int32 NewCount);
};
