// Midnight Madness, Inc.


#include "AbilitySystem/Abilities/GoliathGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/GoliathAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

void UGoliathGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	
	if (AbilityActivationPolicy == EGoliathAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive()) ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
	}
}

void UGoliathGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	if (AbilityActivationPolicy == EGoliathAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo) ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
	}
}

UPawnCombatComponent* UGoliathGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UGoliathAbilitySystemComponent* UGoliathGameplayAbility::GetGoliathAbilitySystemComponentFromActorInfo() const
{
	return Cast<UGoliathAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UGoliathGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle)
{
	auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	check(TargetASC && InSpecHandle.IsValid());
	return GetGoliathAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);
}

FActiveGameplayEffectHandle UGoliathGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle, EGoliathSuccessType& OutSuccessType)
{
	auto ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);
	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EGoliathSuccessType::Successful : EGoliathSuccessType::Failed;
	return ActiveGameplayEffectHandle;
}
