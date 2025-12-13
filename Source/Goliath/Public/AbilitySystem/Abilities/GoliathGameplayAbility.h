// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Types/GoliathEnumTypes.h"
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

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;

	UFUNCTION(BlueprintPure, Category = "Goliath|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Goliath|Ability")
	UGoliathAbilitySystemComponent* GetGoliathAbilitySystemComponentFromActorInfo() const;
	
	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);
	
	UFUNCTION(BlueprintCallable, Category = "Goliath|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EGoliathSuccessType& OutSuccessType);

	UPROPERTY(EditDefaultsOnly, Category = "Goliath|Ability")
	EGoliathAbilityActivationPolicy AbilityActivationPolicy = EGoliathAbilityActivationPolicy::OnTriggered;
};
