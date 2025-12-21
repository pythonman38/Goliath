// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_OrientToTargetActor.generated.h"


UCLASS()
class GOLIATH_API UBTS_OrientToTargetActor : public UBTService
{
	GENERATED_BODY()
	
	UBTS_OrientToTargetActor();
	
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	
	virtual FString GetStaticDescription() const override;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, Category = Target)
	FBlackboardKeySelector InTargetActorKey;
	
	UPROPERTY(EditAnywhere, Category = Target)
	float RotationInterpSpeed;
};
