// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"

class AGoliathHeroWeapon;

UCLASS()
class GOLIATH_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Goliath|Combat")
	AGoliathHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;
	
	UFUNCTION(BlueprintCallable, Category = "Goliath|Combat")
	AGoliathHeroWeapon* GetHeroCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintPure, Category = "Goliath|Combat")
	float GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel);
	
	virtual void OnHitTargetActor(AActor* HitActor) override;
	
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
};
