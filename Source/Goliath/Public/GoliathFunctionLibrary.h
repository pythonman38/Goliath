// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/GoliathEnumTypes.h"
#include "GoliathFunctionLibrary.generated.h"


struct FGameplayEffectSpecHandle;
struct FScalableFloat;
class UPawnCombatComponent;
class UGoliathAbilitySystemComponent;

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
	
	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);
	
	UFUNCTION(BlueprintCallable, Category = "Goliath|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EGoliathValidType& OutValidType);
	
	UFUNCTION(BlueprintPure, Category = "Goliath|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);
	
	UFUNCTION(BlueprintPure, Category = "Goliath|FunctionLibrary", meta = (CompactNodeTitle = "Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel = 1.f);
	
	UFUNCTION(BlueprintPure, Category = "Goliath|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictum, float& OutAngleDifference);
	
	UFUNCTION(BlueprintPure, Category = "Goliath|FunctionLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);
	
	UFUNCTION(BlueprintCallable, Category = "Goliath|FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle);
	
	UFUNCTION(BlueprintCallable, Category = "Goliath|FunctionLibrary", meta = (Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo", 
		ExpandEnumAsExecs = "CountDownInput|CountDownOutput", TotalTime = "1.0", UpdateInterval = "0.1"))
	static void CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime, 
		EGoliathCountDownActionInput CountDownInput, UPARAM(DisplayName = "Output") EGoliathCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo);
};
