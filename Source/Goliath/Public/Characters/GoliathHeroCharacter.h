// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GoliathBaseCharacter.h"
#include "GoliathHeroCharacter.generated.h"

class UHeroUI_Component;
class UHeroCombatComponent;
class UDataAsset_InputConfig;
class UCameraComponent;
class USpringArmComponent;

struct FInputActionValue;

UCLASS()
class GOLIATH_API AGoliathHeroCharacter : public AGoliathBaseCharacter
{
	GENERATED_BODY()

public:
	AGoliathHeroCharacter();
	
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	
	virtual UPawnUI_Component* GetPawnUI_Component() const override;
	
	virtual UHeroUI_Component* GetHeroUI_Component() const override;

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void BeginPlay() override;

private:
	void Input_Move(const FInputActionValue& InputActionValue);
	
	void Input_Look(const FInputActionValue& InputActionValue);
	
	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	
	void Input_AbilityInputReleased(FGameplayTag InInputTag);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = true))
	TObjectPtr<UHeroCombatComponent> HeroCombatComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = true))
	TObjectPtr<UHeroUI_Component> HeroUI_Component;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = CharacterData, meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataAsset_InputConfig> InputConfigDataAsset;
	
public:
	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const { return HeroCombatComponent; }
};
