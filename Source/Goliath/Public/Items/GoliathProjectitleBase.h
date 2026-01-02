// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "GoliathProjectitleBase.generated.h"

struct FGameplayEventData;
class UProjectileMovementComponent;
class UBoxComponent;
class UNiagaraComponent;

UENUM(BlueprintType)
enum class EProjectileDamagePolicy : uint8
{
	OnHit,
	OnBeginOverlap
};

UCLASS()
class GOLIATH_API AGoliathProjectitleBase : public AActor
{
	GENERATED_BODY()

public:
	AGoliathProjectitleBase();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	virtual void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Spawn Projectile Hit FX"))
	void BP_OnSpawnProjectileHitFX(const FVector& HitLocation);
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Projectile)
	TObjectPtr<UBoxComponent> ProjectileCollisionBox;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Projectile)
	TObjectPtr<UNiagaraComponent> ProjectileNiagaraComponent;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Projectile)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
	EProjectileDamagePolicy ProjectileDamagePolicy;
	
	UPROPERTY(BlueprintReadOnly, Category = Projectile, meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle ProjectileDamageEffectSpecHandle;
	
private:
	void HandleApplyProjectileDamage(APawn* InHitPawn, const FGameplayEventData& InPayload);
};
