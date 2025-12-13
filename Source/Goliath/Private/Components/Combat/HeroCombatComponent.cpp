// Midnight Madness, Inc.


#include "Components/Combat/HeroCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTags/GoliathGameplayTags.h"
#include "Items/Weapons/GoliathHeroWeapon.h"


AGoliathHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AGoliathHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AGoliathHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<AGoliathHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel)
{
	return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor)) return;
	
	OverlappedActors.AddUnique(HitActor);
	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), GoliathGameplayTags::Shared_Event_MeleeHit, Data);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), GoliathGameplayTags::Player_Event_HitPause, FGameplayEventData());
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), GoliathGameplayTags::Player_Event_HitPause, FGameplayEventData());
}


