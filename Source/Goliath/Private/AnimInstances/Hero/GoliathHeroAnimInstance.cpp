// Midnight Madness, Inc.


#include "AnimInstances/Hero/GoliathHeroAnimInstance.h"

#include "Characters/GoliathHeroCharacter.h"

void UGoliathHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter) OwningHeroCharacter = Cast<AGoliathHeroCharacter>(OwningCharacter);
}

void UGoliathHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (bHasAcceleration)
	{
		IdleElapsedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = IdleElapsedTime >= EnterRelaxStateThreshold;
	}
}
