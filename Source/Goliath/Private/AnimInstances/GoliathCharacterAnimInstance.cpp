// Midnight Madness, Inc.


#include "AnimInstances/GoliathCharacterAnimInstance.h"

#include "Characters/GoliathBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UGoliathCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AGoliathBaseCharacter>(TryGetPawnOwner());
	if (OwningCharacter) OwningMovementComponent = OwningCharacter->GetCharacterMovement();
}

void UGoliathCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent) return;

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
