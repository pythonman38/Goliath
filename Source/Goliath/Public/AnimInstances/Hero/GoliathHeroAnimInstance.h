// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/GoliathCharacterAnimInstance.h"
#include "GoliathHeroAnimInstance.generated.h"


class AGoliathHeroCharacter;

UCLASS()
class GOLIATH_API UGoliathHeroAnimInstance : public UGoliathCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|References")
	TObjectPtr<AGoliathHeroCharacter> OwningHeroCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float EnterRelaxStateThreshold = 5.f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float IdleElapsedTime;
};
