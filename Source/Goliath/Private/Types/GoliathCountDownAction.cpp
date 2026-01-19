// Midnight Madness, Inc.


#include "Types/GoliathCountDownAction.h"


void FGoliathCountDownAction::CancelAction()
{
	bNeedToCancel = true;
}

void FGoliathCountDownAction::UpdateOperation(FLatentResponse& Response)
{
	if (bNeedToCancel)
	{
		CountDownOutput = EGoliathCountDownActionOutput::Cancelled;
		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		return;
	}
	
	if (ElapsedTimeSinceStart >= TotalCountDownTime)
	{
		CountDownOutput = EGoliathCountDownActionOutput::Completed;
		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		return;
	}
	
	if (ElapsedInterval < UpdateInterval) ElapsedInterval += Response.ElapsedTime();
	else
	{
		ElapsedTimeSinceStart += UpdateInterval > 0.f ? UpdateInterval : Response.ElapsedTime();
		OutRemainingTime = TotalCountDownTime - ElapsedTimeSinceStart;
		CountDownOutput = EGoliathCountDownActionOutput::Updated;
		Response.TriggerLink(ExecutionFunction, OutputLink, CallbackTarget);
		ElapsedInterval = 0.f;
	}
}
