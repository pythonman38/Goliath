// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/GoliathBaseAnimInstance.h"
#include "GoliathHeroLinkedAnimLayer.generated.h"


class UGoliathHeroAnimInstance;

UCLASS()
class GOLIATH_API UGoliathHeroLinkedAnimLayer : public UGoliathBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UGoliathHeroAnimInstance* GetHeroAnimInstance() const;
};
