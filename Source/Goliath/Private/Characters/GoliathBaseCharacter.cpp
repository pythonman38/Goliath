// Midnight Madness, Inc.


#include "Characters/GoliathBaseCharacter.h"

#include "AbilitySystem/GoliathAbilitySystemComponent.h"
#include "AbilitySystem/GoliathAttributeSet.h"


AGoliathBaseCharacter::AGoliathBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;
	
	GoliathAbilitySystemComponent = CreateDefaultSubobject<UGoliathAbilitySystemComponent>("AbilitySystemComp");
	GoliathAttributeSet = CreateDefaultSubobject<UGoliathAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AGoliathBaseCharacter::GetAbilitySystemComponent() const
{
	return GoliathAbilitySystemComponent;
}

UPawnCombatComponent* AGoliathBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

UPawnUI_Component* AGoliathBaseCharacter::GetPawnUI_Component() const
{
	return nullptr;
}

void AGoliathBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (GoliathAbilitySystemComponent)
	{
		GoliathAbilitySystemComponent->InitAbilityActorInfo(this, this);
		ensureMsgf(!CharacterStartupData.IsNull(), TEXT("Forgot to assign start up data to %s!"), *GetName());
	}
}



