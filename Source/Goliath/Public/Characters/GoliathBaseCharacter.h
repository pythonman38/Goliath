// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUI_Interface.h"
#include "GoliathBaseCharacter.generated.h"

class UDataAsset_StartupDataBase;
class UGoliathAttributeSet;
class UGoliathAbilitySystemComponent;
class UMotionWarpingComponent;

UCLASS()
class GOLIATH_API AGoliathBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUI_Interface
{
	GENERATED_BODY()

public:
	AGoliathBaseCharacter();
	
	// Implements AbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	// Implements PawnCombatInterface
	virtual  UPawnCombatComponent* GetPawnCombatComponent() const override;
	
	// Implements PawnUI_Interface
	virtual UPawnUI_Component* GetPawnUI_Component() const override;
	
protected:
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilitySystem)
	TObjectPtr<UGoliathAbilitySystemComponent> GoliathAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilitySystem)
	TObjectPtr<UGoliathAttributeSet> GoliathAttributeSet;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MotionWarping)
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = CharacterData)
	TSoftObjectPtr<UDataAsset_StartupDataBase> CharacterStartupData;
	
public:
	FORCEINLINE UGoliathAbilitySystemComponent* GetGoliathAbilitySystemComponent() const { return GoliathAbilitySystemComponent; }
	FORCEINLINE UGoliathAttributeSet* GetGoliathAttributeSet() const { return GoliathAttributeSet; }
	
};
