// Midnight Madness, Inc.


#include "AbilitySystem/Abilities/GoliathEnemyGameplayAbility.h"

#include "AbilitySystem/GoliathAbilitySystemComponent.h"
#include "Characters/GoliathEnemyCharacter.h"
#include "GameplayTags/GoliathGameplayTags.h"

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

FGameplayEffectSpecHandle UGoliathEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
{
	check(EffectClass);
	
	auto ContextHandle = GetGoliathAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	auto EffectSpecHandle = GetGoliathAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);
	EffectSpecHandle.Data->SetSetByCallerMagnitude(GoliathGameplayTags::Shared_SetByCaller_BaseDamage, InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel()));
	return EffectSpecHandle;
}
