// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GoliathGameplayAbility.generated.h"

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
	
	UPROPERTY(EditDefaultsOnly, Category = GoliathAbility)
	EGoliathAbilityActivationPolicy AbilityActivationPolicy = EGoliathAbilityActivationPolicy::OnTriggered;
};
