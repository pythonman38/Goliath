// Midnight Madness, Inc.


#include "AnimInstances/Hero/GoliathHeroLinkedAnimLayer.h"

#include "AnimInstances/Hero/GoliathHeroAnimInstance.h"

UGoliathHeroAnimInstance* UGoliathHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	return Cast<UGoliathHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
