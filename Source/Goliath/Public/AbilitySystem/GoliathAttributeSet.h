// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GoliathAbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GoliathAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


class IPawnUI_Interface;

UCLASS()
class GOLIATH_API UGoliathAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UGoliathAttributeSet();
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(BlueprintReadOnly, Category = Health)
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UGoliathAttributeSet, CurrentHealth)
	
	UPROPERTY(BlueprintReadOnly, Category = Health)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGoliathAttributeSet, MaxHealth)
	
	UPROPERTY(BlueprintReadOnly, Category = Rage)
	FGameplayAttributeData CurrentRage;
	ATTRIBUTE_ACCESSORS(UGoliathAttributeSet, CurrentRage)
	
	UPROPERTY(BlueprintReadOnly, Category = Rage)
	FGameplayAttributeData MaxRage;
	ATTRIBUTE_ACCESSORS(UGoliathAttributeSet, MaxRage)
	
	UPROPERTY(BlueprintReadOnly, Category = Damage)
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UGoliathAttributeSet, AttackPower)
	
	UPROPERTY(BlueprintReadOnly, Category = Damage)
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UGoliathAttributeSet, DefensePower)
	
	UPROPERTY(BlueprintReadOnly, Category = Damage)
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UGoliathAttributeSet, DamageTaken)
	
private:
	TWeakInterfacePtr<IPawnUI_Interface> CachedPawnUI_Interface;
};
