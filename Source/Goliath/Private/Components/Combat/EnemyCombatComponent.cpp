// Midnight Madness, Inc.


#include "Components/Combat/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GoliathFunctionLibrary.h"
#include "Characters/GoliathEnemyCharacter.h"
#include "Components/BoxComponent.h"
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

void UEnemyCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	auto OwningEnemyCharacter = GetOwningPawn<AGoliathEnemyCharacter>();
	check(OwningEnemyCharacter);
	
	auto LeftHandCollisionBox = OwningEnemyCharacter->GetLeftHandCollisionBox();
	auto RightHandCollisionBox = OwningEnemyCharacter->GetRightHandCollisionBox();
	check(LeftHandCollisionBox && RightHandCollisionBox);
	
	switch (ToggleDamageType)
	{
	case EToggleDamageType::LeftHand:
		LeftHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	case EToggleDamageType::RightHand:
		RightHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	default: 
		break;
	}
	
	if (!bShouldEnable) OverlappedActors.Empty();
}




