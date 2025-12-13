// Midnight Madness, Inc.


#include "Tables/DataAsset_EnemyStartUpData.h"

#include "AbilitySystem/Abilities/GoliathEnemyGameplayAbility.h"
#include "AbilitySystem/GoliathAbilitySystemComponent.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UGoliathAbilitySystemComponent* InASCToGive,
                                                               int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
	
	if (!EnemyCombatAbilities.IsEmpty())
	{
		for (const auto& AbilityClass : EnemyCombatAbilities)
		{
			if (!AbilityClass) continue;
			
			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;
			InASCToGive->GiveAbility(AbilitySpec);
		}
	}
}
