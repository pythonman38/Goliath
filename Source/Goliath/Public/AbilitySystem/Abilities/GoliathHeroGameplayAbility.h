// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GoliathGameplayAbility.h"
#include "GoliathHeroGameplayAbility.generated.h"


class UHeroCombatComponent;
class AGoliathHeroController;
class AGoliathHeroCharacter;

UCLASS()
class GOLIATH_API UGoliathHeroGameplayAbility : public UGoliathGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Goliath|Ability")
	AGoliathHeroCharacter* GetHeroCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Goliath|Ability")
	AGoliathHeroController* GetHeroControllerFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Goliath|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Goliath|Ability")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAtttackTypeTag, int32 InUsedComboCount);
	
	UFUNCTION(BlueprintCallable, Category = "Goliath|Ability")
	bool GetAbilityRemainingCoolDownByTag(FGameplayTag InCoolDownTag, float& TotalCoolDownTime, float& RemainingCoolDownTime);
	
private:
	TWeakObjectPtr<AGoliathHeroCharacter> CachedGoliathHeroCharacter;
	
	TWeakObjectPtr<AGoliathHeroController> CachedGoliathHeroController;
};
