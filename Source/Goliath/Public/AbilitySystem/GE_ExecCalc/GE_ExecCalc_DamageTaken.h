// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GE_ExecCalc_DamageTaken.generated.h"


UCLASS()
class GOLIATH_API UGE_ExecCalc_DamageTaken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UGE_ExecCalc_DamageTaken();
	
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
