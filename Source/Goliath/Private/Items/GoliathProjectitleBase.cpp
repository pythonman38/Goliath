// Midnight Madness, Inc.


#include "Items/GoliathProjectitleBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GoliathFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameplayTags/GoliathGameplayTags.h"


AGoliathProjectitleBase::AGoliathProjectitleBase() :
ProjectileDamagePolicy(EProjectileDamagePolicy::OnHit)
{
	PrimaryActorTick.bCanEverTick = false;
	
	ProjectileCollisionBox = CreateDefaultSubobject<UBoxComponent>("ProjectileCollisionBox");
	SetRootComponent(ProjectileCollisionBox);
	ProjectileCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	ProjectileCollisionBox->OnComponentHit.AddUniqueDynamic(this, &AGoliathProjectitleBase::OnProjectileHit);
	ProjectileCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AGoliathProjectitleBase::OnProjectileBeginOverlap);
	
	ProjectileNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("ProjectileNiagaraComp");
	ProjectileNiagaraComponent->SetupAttachment(GetRootComponent());
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
	ProjectileMovementComponent->InitialSpeed = 700.f;
	ProjectileMovementComponent->MaxSpeed = 900.f;
	ProjectileMovementComponent->Velocity = FVector(1.f, 0.f, 0.f);
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	
	InitialLifeSpan = 4.f;
}

void AGoliathProjectitleBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (ProjectileDamagePolicy == EProjectileDamagePolicy::OnBeginOverlap) ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AGoliathProjectitleBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	BP_OnSpawnProjectileHitFX(Hit.ImpactPoint);
	
	auto HitPawn = Cast<APawn>(OtherActor);
	if (!HitPawn || !UGoliathFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
	{
		Destroy();
		return;
	}
	
	bool bIsValidBlock = false;
	const bool bIsPlayerBlocking = UGoliathFunctionLibrary::NativeDoesActorHaveTag(HitPawn, GoliathGameplayTags::Player_Status_Blocking);
	if (bIsPlayerBlocking) bIsValidBlock = UGoliathFunctionLibrary::IsValidBlock(this, HitPawn);
	
	FGameplayEventData Data;
	Data.Instigator = this;
	Data.Target = HitPawn;
	if (bIsValidBlock) UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitPawn, GoliathGameplayTags::Player_Event_SuccessfulBlock, Data);
	else HandleApplyProjectileDamage(HitPawn, Data);
	Destroy();
}

void AGoliathProjectitleBase::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedActors.Contains(OtherActor)) return;
	
	OverlappedActors.AddUnique(OtherActor);
	if (auto HitPawn = Cast<APawn>(OtherActor))
	{
		FGameplayEventData Data;
		Data.Instigator = GetInstigator();
		Data.Target = HitPawn;
		if (UGoliathFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn)) HandleApplyProjectileDamage(HitPawn, Data);
	}
}

void AGoliathProjectitleBase::HandleApplyProjectileDamage(APawn* InHitPawn, const FGameplayEventData& InPayload)
{
	checkf(ProjectileDamageEffectSpecHandle.IsValid(), TEXT("Forgot to assign a valid spec handle to the projectile: %s!"), *GetActorNameOrLabel());
	
	const auto bWasApplied = UGoliathFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(GetInstigator(), InHitPawn, ProjectileDamageEffectSpecHandle);
	if (bWasApplied)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(InHitPawn, GoliathGameplayTags::Shared_Event_HitReact, InPayload);
	}
}



