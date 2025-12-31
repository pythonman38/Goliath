// Midnight Madness, Inc.


#include "Characters/GoliathHeroCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/GoliathAbilitySystemComponent.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "Components/Input/GoliathInputComponent.h"
#include "Components/UI/HeroUI_Component.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameplayTags/GoliathGameplayTags.h"
#include "Tables/DataAsset_InputConfig.h"
#include "Tables/DataAsset_StartupDataBase.h"


AGoliathHeroCharacter::AGoliathHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	
	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>("HeroCombatComp");
	HeroUI_Component = CreateDefaultSubobject<UHeroUI_Component>("HeroUI_Comp");
}

UPawnCombatComponent* AGoliathHeroCharacter::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

UPawnUI_Component* AGoliathHeroCharacter::GetPawnUI_Component() const
{
	return HeroUI_Component;
}

UHeroUI_Component* AGoliathHeroCharacter::GetHeroUI_Component() const
{
	return HeroUI_Component;
}

void AGoliathHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (GoliathAbilitySystemComponent && GoliathAttributeSet)
	{
		if (!CharacterStartupData.IsNull())
		{
			if (auto LoadedData = CharacterStartupData.LoadSynchronous())
			{
				LoadedData->GiveToAbilitySystemComponent(GoliathAbilitySystemComponent);
			}
		}
	}
}

void AGoliathHeroCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config!"));
	auto LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	auto GoliathInputComponent = CastChecked<UGoliathInputComponent>(PlayerInputComponent);
	GoliathInputComponent->BindNativeInputAction(InputConfigDataAsset, GoliathGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &AGoliathHeroCharacter::Input_Move);
	GoliathInputComponent->BindNativeInputAction(InputConfigDataAsset, GoliathGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &AGoliathHeroCharacter::Input_Look);
	GoliathInputComponent->BindNativeInputAction(InputConfigDataAsset, GoliathGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &AGoliathHeroCharacter::Input_SwitchTargetTriggered);
	GoliathInputComponent->BindNativeInputAction(InputConfigDataAsset, GoliathGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &AGoliathHeroCharacter::Input_SwitchTargetCompleted);
	GoliathInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &AGoliathHeroCharacter::Input_AbilityInputPressed, &AGoliathHeroCharacter::Input_AbilityInputReleased);
}

void AGoliathHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGoliathHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector), RightDirection = MovementRotation.RotateVector(FVector::RightVector);
	if (MovementVector.Y != 0.f) AddMovementInput(ForwardDirection, MovementVector.Y);
	if (MovementVector.X != 0.f) AddMovementInput(RightDirection, MovementVector.X);
}

void AGoliathHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (LookAxisVector.X != 0.f) AddControllerYawInput(LookAxisVector.X);
	if (LookAxisVector.Y != 0.f) AddControllerPitchInput(LookAxisVector.Y);
}

void AGoliathHeroCharacter::Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue)
{
	SwitchDirection = InputActionValue.Get<FVector2D>();
}

void AGoliathHeroCharacter::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, SwitchDirection.X > 0.f ? GoliathGameplayTags::Player_Event_SwitchTarget_Right : 
		GoliathGameplayTags::Player_Event_SwitchTarget_Left, Data);
}

void AGoliathHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	GoliathAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AGoliathHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	GoliathAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}


