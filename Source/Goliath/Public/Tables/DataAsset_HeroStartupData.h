// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset_StartupDataBase.h"
#include "Types/GoliathStructTypes.h"
#include "DataAsset_HeroStartupData.generated.h"


UCLASS()
class GOLIATH_API UDataAsset_HeroStartupData : public UDataAsset_StartupDataBase
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(UGoliathAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = StartUpData, meta = (TitleProperty = InputTag))
	TArray<FGoliathHeroAbilitySet> HeroStartUpAbilitySets;
};
