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
	
private:
	TWeakObjectPtr<AGoliathHeroCharacter> CachedGoliathHeroCharacter;
	
	TWeakObjectPtr<AGoliathHeroController> CachedGoliathHeroController;
};
