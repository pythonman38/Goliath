// Midnight Madness, Inc.


#include "AbilitySystem/Abilities/GoliathHeroGameplayAbility.h"

#include "Characters/GoliathHeroCharacter.h"
#include "Controllers/GoliathHeroController.h"

AGoliathHeroCharacter* UGoliathHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if (!CachedGoliathHeroCharacter.IsValid())
	{
		CachedGoliathHeroCharacter = Cast<AGoliathHeroCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedGoliathHeroCharacter.IsValid() ? CachedGoliathHeroCharacter.Get() : nullptr;
}

AGoliathHeroController* UGoliathHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if (!CachedGoliathHeroController.IsValid())
	{
		CachedGoliathHeroController = Cast<AGoliathHeroController>(CurrentActorInfo->PlayerController);
	}
	return CachedGoliathHeroController.IsValid() ? CachedGoliathHeroController.Get() : nullptr;
}

UHeroCombatComponent* UGoliathHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}
