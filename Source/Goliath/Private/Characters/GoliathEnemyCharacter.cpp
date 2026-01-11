// Midnight Madness, Inc.


#include "Characters/GoliathEnemyCharacter.h"

#include "GoliathFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Components/UI/EnemyUI_Component.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Tables/DataAsset_EnemyStartUpData.h"
#include "Widgets/GoliathWidgetBase.h"


AGoliathEnemyCharacter::AGoliathEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;
	
	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComp");
	EnemyUI_Component = CreateDefaultSubobject<UEnemyUI_Component>("EnemyUI_Comp");
	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("EnemyHealthWidgetComp");
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());
	
	LeftHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("LeftHandCollisionBox");
	LeftHandCollisionBox->SetupAttachment(GetMesh());
	LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AGoliathEnemyCharacter::OnBodyCollisionBoxBeginOverlap);
	
	RightHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("RightHandCollisionBox");
	RightHandCollisionBox->SetupAttachment(GetMesh());
	RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AGoliathEnemyCharacter::OnBodyCollisionBoxBeginOverlap);
}

UPawnCombatComponent* AGoliathEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UPawnUI_Component* AGoliathEnemyCharacter::GetPawnUI_Component() const
{
	return EnemyUI_Component;
}

UEnemyUI_Component* AGoliathEnemyCharacter::GetEnemyUI_Component() const
{
	return EnemyUI_Component;
}

void AGoliathEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitEnemyStartUpData();
}

void AGoliathEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto HealthWidget = Cast<UGoliathWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}
}

#if WITH_EDITOR
void AGoliathEnemyCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, LeftHandCollisionBoxAttachBoneName))
	{
		LeftHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftHandCollisionBoxAttachBoneName);
	}
	
	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, RightHandCollisionBoxAttachBoneName))
	{
		RightHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightHandCollisionBoxAttachBoneName);
	}
}
#endif


void AGoliathEnemyCharacter::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto HitPawn = Cast<APawn>(OtherActor))
	{
		if (UGoliathFunctionLibrary::IsTargetPawnHostile(this, HitPawn)) EnemyCombatComponent->OnHitTargetActor(HitPawn);
	}
}

void AGoliathEnemyCharacter::InitEnemyStartUpData()
{
	if (CharacterStartupData.IsNull()) return;
	
	UAssetManager::GetStreamableManager().RequestAsyncLoad(CharacterStartupData.ToSoftObjectPath(), FStreamableDelegate::CreateLambda(
		[this]()
		{
			if (auto LoadedData = CharacterStartupData.Get()) LoadedData->GiveToAbilitySystemComponent(GoliathAbilitySystemComponent);
		}));
}

