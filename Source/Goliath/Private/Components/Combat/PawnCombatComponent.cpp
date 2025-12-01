// Midnight Madness, Inc.


#include "Components/Combat/PawnCombatComponent.h"

#include "Items/Weapons/GoliathWeaponBase.h"
#include "Singletons/GoliathDebugHelper.h"


void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag inWeaponTagToRegister,
                                                 AGoliathWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(inWeaponTagToRegister), TEXT("A named %s has already been added as carried weapon!"), *inWeaponTagToRegister.ToString());
	check(InWeaponToRegister);
	
	CharacterCarriedWeaponMap.Emplace(inWeaponTagToRegister, InWeaponToRegister);
	if (bRegisterAsEquippedWeapon) CurrentEquippedWeaponTag = inWeaponTagToRegister;
	
	const FString WeaponString = FString::Printf(TEXT("A weapon named: %s has been registered using the tag %s!"), *InWeaponToRegister->GetName(), *inWeaponTagToRegister.ToString());
	Debug::Print(WeaponString);
}

AGoliathWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (auto const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet)) return *FoundWeapon;
	}
	return nullptr;
}

AGoliathWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid()) return nullptr;
	
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}
