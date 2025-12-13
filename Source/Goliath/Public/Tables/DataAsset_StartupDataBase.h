// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartupDataBase.generated.h"


class UGameplayEffect;
class UGoliathAbilitySystemComponent;
class UGoliathGameplayAbility;

UCLASS()
class GOLIATH_API UDataAsset_StartupDataBase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(UGoliathAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
	
protected:
	void GrantAbilities(const TArray<TSubclassOf<UGoliathGameplayAbility>>& InAbilitiesToGive, UGoliathAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
	
	UPROPERTY(EditDefaultsOnly, Category = StartUpData)
	TArray<TSubclassOf<UGoliathGameplayAbility>> ActivateOnGivenAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = StartUpData)
	TArray<TSubclassOf<UGoliathGameplayAbility>> ReactiveAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = StartUpData)
	TArray<TSubclassOf<UGameplayEffect>> StartupGameplayEffects;
};
