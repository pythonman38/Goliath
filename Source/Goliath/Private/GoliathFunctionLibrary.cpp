// Midnight Madness, Inc.


#include "GoliathFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "AbilitySystem/GoliathAbilitySystemComponent.h"
#include "GameplayTags/GoliathGameplayTags.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Types/GoliathCountDownAction.h"

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

bool UGoliathFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);
	auto QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	auto TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());
	return QueryTeamAgent && TargetTeamAgent && QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
}

float UGoliathFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UGoliathFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictum,
	float& OutAngleDifference)
{
	check(InAttacker && InVictum);
	
	const FVector VictumForward = InVictum->GetActorForwardVector(), 
		VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictum->GetActorLocation()).GetSafeNormal();
	const float DotResult = FVector::DotProduct(VictumForward, VictimToAttackerNormalized);
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);
	const FVector CrossResult = FVector::CrossProduct(VictumForward, VictimToAttackerNormalized);
	if (CrossResult.Z < 0.f) OutAngleDifference *= -1.f;
	if (OutAngleDifference >= -45.f && OutAngleDifference <= 45.f) return GoliathGameplayTags::Shared_Status_HitReact_Front;
	if (OutAngleDifference < -45.f && OutAngleDifference >= -135.f) return GoliathGameplayTags::Shared_Status_HitReact_Left;
	if (OutAngleDifference < -135.f || OutAngleDifference > 135.f) return GoliathGameplayTags::Shared_Status_HitReact_Back;
	if (OutAngleDifference > 45.f && OutAngleDifference <= 135.f) return GoliathGameplayTags::Shared_Status_HitReact_Right;
	return GoliathGameplayTags::Shared_Status_HitReact_Front;
}

bool UGoliathFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);
	
	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());
	return DotResult < -0.1f;
}

bool UGoliathFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	auto SourceASC = NativeGetGoliathASCFromActor(InInstigator);
	auto TargetASC = NativeGetGoliathASCFromActor(InTargetActor);
	auto ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);
	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

void UGoliathFunctionLibrary::CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval,
	float& OutRemainingTime, EGoliathCountDownActionInput CountDownInput,
	UPARAM(DisplayName = "Output") EGoliathCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo)
{
	UWorld* World = nullptr;
	if (GEngine) World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World) return;
	auto& LatentActionManager = World->GetLatentActionManager();
	auto FoundAction = LatentActionManager.FindExistingAction<FGoliathCountDownAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);
	if (CountDownInput == EGoliathCountDownActionInput::Start && !FoundAction)
	{
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, 
			new FGoliathCountDownAction(TotalTime, UpdateInterval, OutRemainingTime, CountDownOutput, LatentInfo));
	}
	if (CountDownInput == EGoliathCountDownActionInput::Cancel && FoundAction) FoundAction->CancelAction();
}
