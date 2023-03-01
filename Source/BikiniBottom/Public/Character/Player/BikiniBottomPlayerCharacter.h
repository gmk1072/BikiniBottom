// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BikiniBottomCharacterBase.h"
#include "InputActionValue.h"
#include "Player/BikiniBottomPlayerState.h"
#include "BikiniBottomPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BIKINIBOTTOM_API ABikiniBottomPlayerCharacter : public ABikiniBottomCharacterBase
{
	GENERATED_BODY()
	
public:
	ABikiniBottomPlayerCharacter(const class FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	class USpringArmComponent* GetCameraBoom();

	class UCameraComponent* GetFollowCamera();

	UFUNCTION(BlueprintCallable, Category = "BikiniBottom|Camera")
	float GetStartingCameraBoomArmLength();

	UFUNCTION(BlueprintCallable, Category = "BikiniBottom|Camera")
	FVector GetStartingCameraBoomLocation();



protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BikiniBottom|Camera")
	float BaseTurnRate = 45.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BikiniBottom|Camera")
	float BaseLookUpRate = 45.0f;

	UPROPERTY(BlueprintReadOnly, Category = "BikiniBottom|Camera")
	float StartingCameraBoomArmLength;

	UPROPERTY(BlueprintReadOnly, Category = "BikiniBottom|Camera")
	FVector StartingCameraBoomArmLocation;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "BikiniBottom|Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "BikiniBottom|Camera")
	class UCameraComponent* FollowCamera;

	bool bASCInputBound = false;

	FGameplayTag DeadTag;

	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void LookUp(float Value);

	void LookUpRate(float Value);

	void Turn(float Value);

	void TurnRate(float Value);

	void MoveForward(float Value);

	void MoveRight(float Value);

	virtual void OnRep_PlayerState() override;

	void BindASCInput();

	void InitializeStartingValues(ABikiniBottomPlayerState* PS);

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;
};
