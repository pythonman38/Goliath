// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GoliathBaseCharacter.generated.h"

class UDataAsset_StartupDataBase;
class UGoliathAttributeSet;
class UGoliathAbilitySystemComponent;

UCLASS()
class GOLIATH_API AGoliathBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGoliathBaseCharacter();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilitySystem)
	TObjectPtr<UGoliathAbilitySystemComponent> GoliathAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilitySystem)
	TObjectPtr<UGoliathAttributeSet> GoliathAttributeSet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = CharacterData)
	TSoftObjectPtr<UDataAsset_StartupDataBase> CharacterStartupData;
	
public:
	FORCEINLINE UGoliathAbilitySystemComponent* GetGoliathAbilitySystemComponent() const { return GoliathAbilitySystemComponent; }
	FORCEINLINE UGoliathAttributeSet* GetGoliathAttributeSet() const { return GoliathAttributeSet; }
	
};
