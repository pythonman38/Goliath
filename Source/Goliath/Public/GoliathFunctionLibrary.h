// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GoliathFunctionLibrary.generated.h"


class UGoliathAbilitySystemComponent;

UENUM()
enum class EGoliathConfirmType : uint8
{
	Yes,
	No
};

UCLASS()
class GOLIATH_API UGoliathFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static UGoliathAbilitySystemComponent* NativeGetGoliathASCFromActor(AActor* InActor);
	
	UFUNCTION(BlueprintCallable, Category = "Goliath|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);
	
	UFUNCTION(BlueprintCallable, Category = "Goliath|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);
	
	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);
	
	UFUNCTION(BlueprintCallable, Category = "Goliath|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EGoliathConfirmType& OutConfirmType);
};
