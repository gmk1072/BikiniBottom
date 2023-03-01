// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BikiniBottomPlayerState.h"
#include "Character/Abilities/AttributesSets/CharacterAttributeSetBase.h"
#include "Character/Abilities/CharacterAbilitySystemComponent.h"

ABikiniBottomPlayerState::ABikiniBottomPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCharacterAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSetBase = CreateDefaultSubobject<UCharacterAttributeSetBase>(TEXT("AttributeSetBase"));

	NetUpdateFrequency = 100.0f;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

UAbilitySystemComponent* ABikiniBottomPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UCharacterAttributeSetBase* ABikiniBottomPlayerState::GetAttributeSetBase() const
{
	return AttributeSetBase;
}

bool ABikiniBottomPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}

void ABikiniBottomPlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
	//TODO -- implement HUD later
}

int32 ABikiniBottomPlayerState::GetCharacterLevel() const
{
	return AttributeSetBase->GetLevel();
}

float ABikiniBottomPlayerState::GetHealth() const
{
	return AttributeSetBase->GetHealth();
}

float ABikiniBottomPlayerState::GetMaxHealth() const
{
	return AttributeSetBase->GetMaxHealth();
}

void ABikiniBottomPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		CharacterLevelChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetLevelAttribute()).AddUObject(this, &ABikiniBottomPlayerState::CharacterLevelChanged);
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &ABikiniBottomPlayerState::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &ABikiniBottomPlayerState::MaxHealthChanged);
	}
	AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ABikiniBottomPlayerState::StunTagChanged);
}

void ABikiniBottomPlayerState::CharacterLevelChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Level Changed!"));
}

void ABikiniBottomPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Health Changed!"));

}

void ABikiniBottomPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Max Health Changed!"));

}

void ABikiniBottomPlayerState::StunTagChanged(const FGameplayTag CallbaackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));

		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToIgnore.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.NotCanceledByStun")));

		AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);
	}
}

