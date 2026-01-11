// Midnight Madness, Inc.


#include "Components/Combat/PawnCombatComponent.h"

#include "Components/BoxComponent.h"
#include "Items/Weapons/GoliathWeaponBase.h"
#include "Singletons/GoliathDebugHelper.h"


void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag inWeaponTagToRegister,
                                                 AGoliathWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(inWeaponTagToRegister), TEXT("A named %s has already been added as carried weapon!"), *inWeaponTagToRegister.ToString());
	check(InWeaponToRegister);
	
	CharacterCarriedWeaponMap.Emplace(inWeaponTagToRegister, InWeaponToRegister);
	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &UPawnCombatComponent::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &UPawnCombatComponent::OnWeaponPulledFromTargetActor);
	if (bRegisterAsEquippedWeapon) CurrentEquippedWeaponTag = inWeaponTagToRegister;
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

void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon) ToggleCurrentEquippedWeaponCollision(bShouldEnable);
	else ToggleBodyCollisionBoxCollision(bShouldEnable, ToggleDamageType);
}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
}

void UPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}

void UPawnCombatComponent::ToggleCurrentEquippedWeaponCollision(bool bShouldEnable)
{
	auto WeaponToToggle = GetCharacterCurrentEquippedWeapon();
	check(WeaponToToggle);
		
	WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
	if (!bShouldEnable) OverlappedActors.Empty();
}

void UPawnCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
}
