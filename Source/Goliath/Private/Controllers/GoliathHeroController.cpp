// Midnight Madness, Inc.


#include "Controllers/GoliathHeroController.h"

AGoliathHeroController::AGoliathHeroController()
{
	HeroTeamId = FGenericTeamId(0);
}

FGenericTeamId AGoliathHeroController::GetGenericTeamId() const
{
	return HeroTeamId;
}
