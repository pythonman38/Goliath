// Midnight Madness, Inc.


#include "Components/Combat/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GoliathFunctionLibrary.h"
#include "GameplayTags/GoliathGameplayTags.h"

UEnemyCombatComponent::UEnemyCombatComponent()
{
}

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor)) return;
	
	OverlappedActors.AddUnique(HitActor);
	bool bIsValidBlock = false;
	const bool bIsPlayerBlocking = UGoliathFunctionLibrary::NativeDoesActorHaveTag(HitActor, GoliathGameplayTags::Player_Status_Blocking), 
		bIsMyAttackUnblockable = UGoliathFunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), GoliathGameplayTags::Enemy_Status_Unblockable);
	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock = UGoliathFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}
	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;
	if (bIsValidBlock) UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, GoliathGameplayTags::Player_Event_SuccessfulBlock, EventData);
	else UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), GoliathGameplayTags::Shared_Event_MeleeHit, EventData);
}




