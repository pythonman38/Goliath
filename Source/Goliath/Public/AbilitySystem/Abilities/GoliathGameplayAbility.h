// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GoliathGameplayAbility.generated.h"

class UGoliathAbilitySystemComponent;
class UPawnCombatComponent;

UENUM(BlueprintType)
enum class EGoliathAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

UCLASS()
class GOLIATH_API UGoliathGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UFUNCTION(BlueprintPure, Category = "Goliath|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;
	
	UFUNCTION(BlueprintCallable, Category = "Goliath|Ability")
	UGoliathAbilitySystemComponent* GetGoliathAbilitySystemComponentFromActorInfo() const;
	
	UPROPERTY(EditDefaultsOnly, Category = "Goliath|Ability")
	EGoliathAbilityActivationPolicy AbilityActivationPolicy = EGoliathAbilityActivationPolicy::OnTriggered;
	
	
};
