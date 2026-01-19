// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GoliathEnumTypes.h"

class FGoliathCountDownAction : public FPendingLatentAction
{
public:
	FGoliathCountDownAction(float InTotalCountDownTime, float InUpdateInterval, float& InOutRemainingTime, EGoliathCountDownActionOutput& InCountDownOutput, 
		const FLatentActionInfo& LatentInfo)
		: bNeedToCancel(false)
		, TotalCountDownTime(InTotalCountDownTime)
		, UpdateInterval(InUpdateInterval)
		, OutRemainingTime(InOutRemainingTime)
		, CountDownOutput(InCountDownOutput)
		, ExecutionFunction(LatentInfo.ExecutionFunction)
		, OutputLink(LatentInfo.Linkage)
		, CallbackTarget(LatentInfo.CallbackTarget)
		, ElapsedInterval(0.f)
		, ElapsedTimeSinceStart(0.f)
	{}
	
	void CancelAction();
	
	virtual void UpdateOperation(FLatentResponse& Response) override;
	
private:
	bool bNeedToCancel;
	
	float TotalCountDownTime, UpdateInterval;
	
	float& OutRemainingTime;
	
	EGoliathCountDownActionOutput& CountDownOutput;
	
	FName ExecutionFunction;
	
	int32 OutputLink;
	
	FWeakObjectPtr CallbackTarget;
	
	float ElapsedInterval, ElapsedTimeSinceStart;
};
