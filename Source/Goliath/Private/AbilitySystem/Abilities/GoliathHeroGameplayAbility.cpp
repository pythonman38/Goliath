// Midnight Madness, Inc.


#include "AbilitySystem/Abilities/GoliathHeroGameplayAbility.h"

#include "AbilitySystem/GoliathAbilitySystemComponent.h"
#include "Characters/GoliathHeroCharacter.h"
#include "Controllers/GoliathHeroController.h"
#include "GameplayTags/GoliathGameplayTags.h"

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

FGameplayEffectSpecHandle UGoliathHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAtttackTypeTag,
	int32 InUsedComboCount)
{
	check(EffectClass);
	
	auto ContextHandle = GetGoliathAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	auto EffectSpecHandle = GetGoliathAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);
	EffectSpecHandle.Data->SetSetByCallerMagnitude(GoliathGameplayTags::Shared_SetByCaller_BaseDamage, InWeaponBaseDamage);
	if (InCurrentAtttackTypeTag.IsValid()) EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAtttackTypeTag, InUsedComboCount);
	return EffectSpecHandle;
}
