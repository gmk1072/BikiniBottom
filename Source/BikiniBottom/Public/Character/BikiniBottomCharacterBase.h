// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BikiniBottom/BikiniBottom.h"
#include "GameplayTagContainer.h"
#include "BikiniBottomCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, ABikiniBottomCharacterBase*, Character);


UCLASS()
class BIKINIBOTTOM_API ABikiniBottomCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABikiniBottomCharacterBase(const class FObjectInitializer& ObjectInitializer);

	//// Called every frame
	//virtual void Tick(float DeltaTime) override;

	//// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(BlueprintAssignable, Category = "BikiniBottom|Character")
	FCharacterDiedDelegate OnCharacterDied;
	
	UFUNCTION(BlueprintCallable, Category = "BikiniBottom|Character")
	virtual bool IsAlive() const;
	
	UFUNCTION(BlueprintCallable, Category = "BikiniBottom|Character")
	virtual int32 GetAbilityLevel(BikiniBottomAbilityID AbilityID) const;

	virtual void RemoveCharacterAbilities();

	virtual void Die();

	UFUNCTION(BlueprintCallable, Category = "BikiniBottom|Character")
	virtual void FinishDying();

	UFUNCTION(BlueprintCallable, Category = "BikiniBottom|Character|Attributes")
	float GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable, Category = "BikiniBottom|Character|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "BikiniBottom|Character|Attributes")
	float GetMaxHealth() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TWeakObjectPtr<class UCharacterAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<class UCharacterAttributeSetBase> AttributeSetBase;

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "BikiniBottom|Character")
	FText CharacterName;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BikiniBottom|Animation")
	UAnimMontage* DeathMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BikiniBottom|Animation")
	TArray <TSubclassOf<class UCharacterGameplayAbility>> CharacterAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "BikiniBottom|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "BikiniBottom|Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	virtual void AddCharacterAbilities();

	virtual void InitializeAttributes();

	virtual void AddStartupEffects();

	virtual void SetHealth(float Health);

};
