// Midnight Madness, Inc.


#include "AI/BTS_OrientToTargetActor.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTS_OrientToTargetActor::UBTS_OrientToTargetActor()
{
	NodeName = TEXT("Native Orient Rotation To Target Actor");
	
	INIT_SERVICE_NODE_NOTIFY_FLAGS();
	
	RotationInterpSpeed = 5.f;
	Interval = 0.f;
	RandomDeviation = 0.f;
	InTargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, InTargetActorKey), AActor::StaticClass());
}

void UBTS_OrientToTargetActor::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	
	if (auto BBAsset = GetBlackboardAsset()) InTargetActorKey.ResolveSelectedKey(*BBAsset);
}

FString UBTS_OrientToTargetActor::GetStaticDescription() const
{
	const FString KeyDescription = InTargetActorKey.SelectedKeyName.ToString();
	return FString::Printf(TEXT("Orient Rotation to %s Key %s"), *KeyDescription, *GetStaticServiceDescription());
}

void UBTS_OrientToTargetActor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	auto ActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(InTargetActorKey.SelectedKeyName);
	auto TargetActor = Cast<AActor>(ActorObject);
	auto OwningPawn = OwnerComp.GetAIOwner()->GetPawn();
	
	if (TargetActor && OwningPawn)
	{
		const auto LookAtRot = UKismetMathLibrary::FindLookAtRotation(OwningPawn->GetActorLocation(), TargetActor->GetActorLocation());
		const auto TargetRot = FMath::RInterpTo(OwningPawn->GetActorRotation(), LookAtRot, DeltaSeconds, RotationInterpSpeed);
		OwningPawn->SetActorRotation(TargetRot);
	}
}
