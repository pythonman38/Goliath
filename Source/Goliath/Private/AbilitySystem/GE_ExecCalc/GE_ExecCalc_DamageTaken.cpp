// Midnight Madness, Inc.


#include "AbilitySystem/GE_ExecCalc/GE_ExecCalc_DamageTaken.h"

#include "AbilitySystem/GoliathAttributeSet.h"
#include "GameplayTags/GoliathGameplayTags.h"
#include "Singletons/GoliathDebugHelper.h"

struct FGoliathDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)
	
	FGoliathDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGoliathAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGoliathAttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGoliathAttributeSet, DamageTaken, Target, false)
	}
};

static const FGoliathDamageCapture& GetGoliathDamageCapture()
{
	static FGoliathDamageCapture GoliathDamageCapture;
	return GoliathDamageCapture;
}

UGE_ExecCalc_DamageTaken::UGE_ExecCalc_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetGoliathDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetGoliathDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetGoliathDamageCapture().DamageTakenDef);
}

void UGE_ExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	const auto& EffectSpec = ExecutionParams.GetOwningSpec();
	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParams.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();
	float SourceAttackPower = 0.f, TargetDefensePower = 0.f, BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0, UsedHeavyAttackComboCount = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetGoliathDamageCapture().AttackPowerDef, EvaluateParams, SourceAttackPower);
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(GoliathGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
		}
		if (TagMagnitude.Key.MatchesTagExact(GoliathGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
		}
		if (TagMagnitude.Key.MatchesTagExact(GoliathGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
		}
	}
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetGoliathDamageCapture().DefensePowerDef, EvaluateParams, TargetDefensePower);
	if (UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05 + 1.f;
		BaseDamage *= DamageIncreasePercentLight;
	}
	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.f;
		BaseDamage *= DamageIncreasePercentHeavy;
	}
	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
	if (FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGoliathDamageCapture().DamageTakenProperty, EGameplayModOp::Override, FinalDamageDone));
	}
}
