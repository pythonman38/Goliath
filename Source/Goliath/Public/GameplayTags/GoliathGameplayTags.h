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
	
	/** Player Weapon Tags **/
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);
	
	/** Player Event Tags **/
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe);
	
	/** Player Status Tags **/
	GOLIATH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);
}
