// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

class AGoliathWeaponBase;

UCLASS()
class GOLIATH_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Goliath|Combat")
	void RegisterSpawnedWeapon(FGameplayTag inWeaponTagToRegister, AGoliathWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);
	
	UFUNCTION(BlueprintCallable, Category = "Goliath|Combat")
	AGoliathWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;
	
	UFUNCTION(BlueprintCallable, Category = "Goliath|Combat")
	AGoliathWeaponBase* GetCharacterCurrentEquippedWeapon() const;
	
	UPROPERTY(BlueprintReadWrite, Category = "Goliath|Combat")
	FGameplayTag CurrentEquippedWeaponTag;
	
private:
	TMap<FGameplayTag, AGoliathWeaponBase*> CharacterCarriedWeaponMap;
};
