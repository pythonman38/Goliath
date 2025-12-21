// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "GoliathHeroController.generated.h"


UCLASS()
class GOLIATH_API AGoliathHeroController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	AGoliathHeroController();
	
	virtual FGenericTeamId GetGenericTeamId() const override;
	
private:
	FGenericTeamId HeroTeamId;
};
