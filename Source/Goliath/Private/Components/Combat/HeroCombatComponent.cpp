// Midnight Madness, Inc.


#include "Components/Combat/HeroCombatComponent.h"

#include "Items/Weapons/GoliathHeroWeapon.h"


AGoliathHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AGoliathHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}
