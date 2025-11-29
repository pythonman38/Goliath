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

void AGoliathBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (GoliathAbilitySystemComponent)
	{
		GoliathAbilitySystemComponent->InitAbilityActorInfo(this, this);
		ensureMsgf(!CharacterStartupData.IsNull(), TEXT("Forgot to assign start up data to %s!"), *GetName());
	}
}



