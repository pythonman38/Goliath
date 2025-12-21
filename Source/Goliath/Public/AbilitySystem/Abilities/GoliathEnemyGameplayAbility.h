// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GoliathGameplayAbility.h"
#include "GoliathEnemyGameplayAbility.generated.h"


class UEnemyCombatComponent;
class AGoliathEnemyCharacter;

UCLASS()
class GOLIATH_API UGoliathEnemyGameplayAbility : public UGoliathGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Goliath|Abilities")
	AGoliathEnemyCharacter* GetEnemyCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Goliath|Abilities")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Goliath|Abilities")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat);
	
private:
	TWeakObjectPtr<AGoliathEnemyCharacter> CachedGoliathEnemyCharacter;
};
