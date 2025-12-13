// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset_StartupDataBase.h"
#include "DataAsset_EnemyStartUpData.generated.h"


class UGoliathEnemyGameplayAbility;

UCLASS()
class GOLIATH_API UDataAsset_EnemyStartUpData : public UDataAsset_StartupDataBase
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(UGoliathAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = StartUpData)
	TArray<TSubclassOf<UGoliathEnemyGameplayAbility>> EnemyCombatAbilities;
};
