// Midnight Madness, Inc.


#include "AnimInstances/GoliathBaseAnimInstance.h"

#include "GoliathFunctionLibrary.h"

bool UGoliathBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (auto OwningPawn = TryGetPawnOwner())
	{
		return UGoliathFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}
	return false;
}
