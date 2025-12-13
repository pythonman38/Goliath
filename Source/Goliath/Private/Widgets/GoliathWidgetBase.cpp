// Midnight Madness, Inc.


#include "Widgets/GoliathWidgetBase.h"

#include "Interfaces/PawnUI_Interface.h"

void UGoliathWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (auto PawnUI_Interface = Cast<IPawnUI_Interface>(GetOwningPlayerPawn()))
	{
		if (auto HeroUI_Component = PawnUI_Interface->GetHeroUI_Component())
		{
			BP_OnOwningHeroUI_ComponentInitialized(HeroUI_Component);
		}
	}
}

void UGoliathWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if (auto PawnUI_Interfae = Cast<IPawnUI_Interface>(OwningEnemyActor))
	{
		auto EnemyUI_Component = PawnUI_Interfae->GetEnemyUI_Component();
		checkf(EnemyUI_Component, TEXT("Failed to extract an Enemy UI Component from %s"), *OwningEnemyActor->GetActorNameOrLabel());
		
		BP_OnOwningEnmeyUI_ComponentInitialized(EnemyUI_Component);
	}
}
