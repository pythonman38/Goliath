// Midnight Madness, Inc.


#include "Tables/DataAsset_HeroStartupData.h"

#include "AbilitySystem/GoliathAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/GoliathGameplayAbility.h"

void UDataAsset_HeroStartupData::GiveToAbilitySystemComponent(UGoliathAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
	
	for (const auto& AbilitySet : HeroStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;
		
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
