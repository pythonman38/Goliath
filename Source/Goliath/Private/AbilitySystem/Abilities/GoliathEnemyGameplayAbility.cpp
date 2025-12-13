// Midnight Madness, Inc.


#include "AbilitySystem/Abilities/GoliathEnemyGameplayAbility.h"

#include "Characters/GoliathEnemyCharacter.h"

AGoliathEnemyCharacter* UGoliathEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedGoliathEnemyCharacter.IsValid())
	{
		CachedGoliathEnemyCharacter = Cast<AGoliathEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedGoliathEnemyCharacter.IsValid() ? CachedGoliathEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UGoliathEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
