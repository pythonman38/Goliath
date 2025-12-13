// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

class AGoliathWeaponBase;

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};

UCLASS()
class GOLIATH_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Goliath|Combat")
	void RegisterSpawnedWeapon(FGameplayTag inWeaponTagToRegister, AGoliathWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);
	
	UFUNCTION(BlueprintCallable, Category = "Goliath|Combat")
	AGoliathWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;
	
	UFUNCTION(BlueprintCallable, Category = "Goliath|Combat")
	AGoliathWeaponBase* GetCharacterCurrentEquippedWeapon() const;
	
	UFUNCTION(BlueprintCallable, Category = "Goliath|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);
	
	virtual void OnHitTargetActor(AActor* HitActor);
	
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);
	
	UPROPERTY(BlueprintReadWrite, Category = "Goliath|Combat")
	FGameplayTag CurrentEquippedWeaponTag;
	
protected:
	TArray<AActor*> OverlappedActors;
	
private:
	TMap<FGameplayTag, AGoliathWeaponBase*> CharacterCarriedWeaponMap;
};
