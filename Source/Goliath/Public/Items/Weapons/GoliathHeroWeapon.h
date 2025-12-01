// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "GoliathWeaponBase.h"
#include "Types/GoliathStructTypes.h"
#include "GoliathHeroWeapon.generated.h"

UCLASS()
class GOLIATH_API AGoliathHeroWeapon : public AGoliathWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = WeaponData)
	FGoliathHeroWeaponData HeroWeaponData;
	
	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);
	
	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;
	
private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
