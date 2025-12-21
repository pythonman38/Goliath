// Midnight Madness, Inc.


#include "Controllers/GoliathAI_Controller.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


AGoliathAI_Controller::AGoliathAI_Controller(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent")),
	bEnableDetourCrowdAvoidance(true),
	DetourCrowdAvoidanceQuality(4),
	CollisionQueryRange(600.f)
{
	AI_SenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("EnemySenseConfig_Sight");
	AI_SenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	AI_SenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	AI_SenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	AI_SenseConfig_Sight->SightRadius = 5000.f;
	AI_SenseConfig_Sight->LoseSightRadius = 0.f;
	AI_SenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f;
	
	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("EnemyPerceptionComp");
	EnemyPerceptionComponent->ConfigureSense(*AI_SenseConfig_Sight);
	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AGoliathAI_Controller::OnEnemyPerceptionUpdated);

	AAIController::SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type AGoliathAI_Controller::GetTeamAttitudeTowards(const AActor& Other) const
{
	const auto PawnToCheck = Cast<APawn>(&Other);
	const auto OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(PawnToCheck->GetController());
	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId()) return ETeamAttitude::Hostile;
	return ETeamAttitude::Friendly;
}

void AGoliathAI_Controller::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		CrowdComp->SetCrowdSimulationState(bEnableDetourCrowdAvoidance ? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);
		switch (DetourCrowdAvoidanceQuality)
		{
			case 1: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low); break;
			case 2: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium); break;
			case 3: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good); break;
			case 4: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High); break;
			default: break;
		}
		CrowdComp->SetAvoidanceGroup(1);
		CrowdComp->SetGroupsToAvoid(1);
		CrowdComp->SetCrowdCollisionQueryRange(CollisionQueryRange);
	}
}

void AGoliathAI_Controller::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (auto BlackBoardComponent = GetBlackboardComponent())
	{
		if (!BlackBoardComponent->GetValueAsObject(FName("TargetActor")))
		{
			if (Stimulus.WasSuccessfullySensed() && Actor) BlackBoardComponent->SetValueAsObject(FName("TargetActor"), Actor);
		}
	}
}
