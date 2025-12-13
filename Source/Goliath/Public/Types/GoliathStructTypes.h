// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "GoliathStructTypes.generated.h"

class UInputMappingContext;
class UGoliathGameplayAbility;
class UGoliathHeroLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FGoliathHeroAbilitySet
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = InputTag))
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGoliathGameplayAbility> AbilityToGrant;
	
	bool IsValid() const;
};

USTRUCT(BlueprintType)
struct FGoliathHeroWeaponData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGoliathHeroLinkedAnimLayer> WeaponAnimLayerToLink;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> WeaponInputMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = InputTag))
	TArray<FGoliathHeroAbilitySet> DefaultWeaponAbilities;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> SoftWeaponIconTexture;
};