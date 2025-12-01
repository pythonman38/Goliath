// Midnight Madness, Inc.


#include "Types/GoliathStructTypes.h"

#include "AbilitySystem/Abilities/GoliathGameplayAbility.h"


bool FGoliathHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
