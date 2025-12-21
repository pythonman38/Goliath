// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace GoliathGameplayTags
{
	/** Player Input Tags **/
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipAxe);
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipAxe);
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Axe);
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Axe);
	
	/** Player Ability Tags **/
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe);
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe);
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe);
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe);
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause);
	
	/** Player Weapon Tags **/
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);
	
	/** Player Event Tags **/
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe);
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPause);
	
	/** Player Status Tags **/
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);
	
	/** Player SetByCaller Tags **/
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light);
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy);
	
	/** Enemy Ability Tags **/
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee);
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);
	
	/** Enemy Weapon Tags **/
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);
	
	/** Enemy Status Tags **/
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Strafing);
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_UnderAttack);
	
	/** Shared Ability Tags **/
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact);
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death);
	
	/** Shared Event Tags **/
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit);
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact);
	
	/** Shared SetByCaller Tags **/
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage);
	
	/** Shared Status Tags **/
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Dead);
	
}
