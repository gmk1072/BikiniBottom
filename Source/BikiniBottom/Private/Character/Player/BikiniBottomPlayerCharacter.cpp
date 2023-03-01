// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/BikiniBottomPlayerCharacter.h"
#include "AI/PlayerAIController.h"
#include "Camera/CameraComponent.h"
#include "Character/Abilities/CharacterAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/BikiniBottomPlayerState.h"
#include "Player/BikiniBottomPlayerController.h"

ABikiniBottomPlayerCharacter::ABikiniBottomPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(0, 0, 70));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(FName("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->FieldOfView = 80.0f;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(FName("NoCollision"));

	AIControllerClass = APlayerAIController::StaticClass();

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

void ABikiniBottomPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABikiniBottomPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABikiniBottomPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ABikiniBottomPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABikiniBottomPlayerCharacter::LookUpRate);
	PlayerInputComponent->BindAxis("Turn", this, &ABikiniBottomPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABikiniBottomPlayerCharacter::TurnRate);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABikiniBottomPlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABikiniBottomPlayerCharacter::Look);

	}


	BindASCInput();
}

void ABikiniBottomPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ABikiniBottomPlayerState* PS = GetPlayerState<ABikiniBottomPlayerState>();

	if (PS)
	{
		InitializeStartingValues(PS);

		AddStartupEffects();
		AddCharacterAbilities();
	}
}

USpringArmComponent* ABikiniBottomPlayerCharacter::GetCameraBoom()
{
	return CameraBoom;
}

UCameraComponent* ABikiniBottomPlayerCharacter::GetFollowCamera()
{
	return FollowCamera;
}

float ABikiniBottomPlayerCharacter::GetStartingCameraBoomArmLength()
{
	return StartingCameraBoomArmLength;
}

FVector ABikiniBottomPlayerCharacter::GetStartingCameraBoomLocation()
{
	return StartingCameraBoomArmLocation;
}

void ABikiniBottomPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	StartingCameraBoomArmLength = CameraBoom->TargetArmLength;
	StartingCameraBoomArmLocation = CameraBoom->GetRelativeLocation();
}

void ABikiniBottomPlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABikiniBottomPlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABikiniBottomPlayerCharacter::LookUp(float Value)
{
	if (IsAlive())
	{
		AddControllerPitchInput(Value);
	}
}

void ABikiniBottomPlayerCharacter::LookUpRate(float Value)
{
	if (IsAlive())
	{
		AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->DeltaTimeSeconds);
	}
}

void ABikiniBottomPlayerCharacter::Turn(float Value)
{
	if (IsAlive())
	{
		AddControllerYawInput(Value);
	}
}

void ABikiniBottomPlayerCharacter::TurnRate(float Value)
{

	if (IsAlive())
	{
		AddControllerYawInput(Value * BaseTurnRate * GetWorld()->DeltaTimeSeconds);
	}
}

void ABikiniBottomPlayerCharacter::MoveForward(float Value)
{
	AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0, GetControlRotation().Yaw, 0)), Value);
}

void ABikiniBottomPlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0, GetControlRotation().Yaw, 0)), Value);
}

void ABikiniBottomPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	ABikiniBottomPlayerState* PS = GetPlayerState<ABikiniBottomPlayerState>();

	if (PS)
	{
		InitializeStartingValues(PS);
		BindASCInput();
		InitializeAttributes();
	}

}
void ABikiniBottomPlayerCharacter::BindASCInput()
{
	if (!bASCInputBound && AbilitySystemComponent.IsValid() && IsValid(InputComponent))
	{
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"), FString("CancelTarget"), FString("BikiniBottomAbilityID"), static_cast<int32>(BikiniBottomAbilityID::Confirm), static_cast<int32>(BikiniBottomAbilityID::Cancel)));

		bASCInputBound = true;
	}
}
void ABikiniBottomPlayerCharacter::InitializeStartingValues(ABikiniBottomPlayerState* PS)
{
	AbilitySystemComponent = Cast<UCharacterAbilitySystemComponent>(PS->GetAbilitySystemComponent());

	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

	AttributeSetBase = PS->GetAttributeSetBase();

	AbilitySystemComponent->SetTagMapCount(DeadTag, 0);

	SetHealth(GetMaxHealth());

}
