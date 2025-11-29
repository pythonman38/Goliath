// Midnight Madness, Inc.


#include "Tables/DataAsset_StartupDataBase.h"

#include "AbilitySystem/GoliathAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/GoliathGameplayAbility.h"

void UDataAsset_StartupDataBase::GiveToAbilitySystemComponent(UGoliathAbilitySystemComponent* InASCToGive,
                                                              int32 ApplyLevel)
{
	check(InASCToGive);
	
	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);
}

void UDataAsset_StartupDataBase::GrantAbilities(const TArray<TSubclassOf<UGoliathGameplayAbility>>& InAbilitiesToGive,
	UGoliathAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty()) return;
	
	for (const auto& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;
		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
