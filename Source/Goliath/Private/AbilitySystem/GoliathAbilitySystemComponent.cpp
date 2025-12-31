// Midnight Madness, Inc.


#include "AbilitySystem/GoliathAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/GoliathHeroGameplayAbility.h"
#include "GameplayTags/GoliathGameplayTags.h"

void UGoliathAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;
	
	for (const auto& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag)) continue;
		
		if (InInputTag.MatchesTag(GoliathGameplayTags::InputTag_Toggleable))
		{
			if (AbilitySpec.IsActive()) CancelAbilityHandle(AbilitySpec.Handle);
			else TryActivateAbility(AbilitySpec.Handle);
		}
		else TryActivateAbility(AbilitySpec.Handle);
	}
}

void UGoliathAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid() || !InInputTag.MatchesTag(GoliathGameplayTags::InputTag_MustBeHeld)) return;
	
	for (const auto& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
	}
}

void UGoliathAbilitySystemComponent::GrantHeroWeaponAbilities(
	const TArray<FGoliathHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if (InDefaultWeaponAbilities.IsEmpty()) return;
	
	for (const auto& AbilitySet : InDefaultWeaponAbilities)
	{
		if (!AbilitySet.IsValid()) continue;
		
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);
		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UGoliathAbilitySystemComponent::RemoveGrantedHeroWeaponAbilities(
	TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if (InSpecHandlesToRemove.IsEmpty()) return;
	
	for (const auto& SpecHandle : InSpecHandlesToRemove)
	{
		if (SpecHandle.IsValid()) ClearAbility(SpecHandle);
	}
	InSpecHandlesToRemove.Empty();
}

bool UGoliathAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
	check(AbilityTagToActivate.IsValid());
	
	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), FoundAbilitySpecs);
	if (!FoundAbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitySpecs.Num() - 1);
		auto SpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];
		check(SpecToActivate);
		
		if (!SpecToActivate->IsActive()) return TryActivateAbility(SpecToActivate->Handle);
	}
	return false;
}
