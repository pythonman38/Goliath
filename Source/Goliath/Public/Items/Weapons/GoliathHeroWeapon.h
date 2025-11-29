// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GoliathWeaponBase.h"
#include "GoliathHeroWeapon.generated.h"

UCLASS()
class GOLIATH_API AGoliathHeroWeapon : public AGoliathWeaponBase
{
	GENERATED_BODY()

public:
	AGoliathHeroWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
