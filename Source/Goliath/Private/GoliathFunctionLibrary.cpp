// Midnight Madness, Inc.


#include "GoliathFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/GoliathAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"

UGoliathAbilitySystemComponent* UGoliathFunctionLibrary::NativeGetGoliathASCFromActor(AActor* InActor)
{
	check(InActor);
	
	return CastChecked<UGoliathAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UGoliathFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	auto ASC = NativeGetGoliathASCFromActor(InActor);
	if (!ASC->HasMatchingGameplayTag(TagToAdd)) ASC->AddLooseGameplayTag(TagToAdd);
}

void UGoliathFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	auto ASC = NativeGetGoliathASCFromActor(InActor);
	if (ASC->HasMatchingGameplayTag(TagToRemove)) ASC->RemoveLooseGameplayTag(TagToRemove);
}

bool UGoliathFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	auto ASC = NativeGetGoliathASCFromActor(InActor);
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UGoliathFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck,
	EGoliathConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EGoliathConfirmType::Yes : EGoliathConfirmType::No;
}

UPawnCombatComponent* UGoliathFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);
	
	if (auto PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}
	return nullptr;
}

UPawnCombatComponent* UGoliathFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor,
	EGoliathValidType& OutValidType)
{
	OutValidType = NativeGetPawnCombatComponentFromActor(InActor) ? EGoliathValidType::Valid : EGoliathValidType::Invalid;
	return NativeGetPawnCombatComponentFromActor(InActor);
}
