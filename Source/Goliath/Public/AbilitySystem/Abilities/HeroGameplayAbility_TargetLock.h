// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GoliathHeroGameplayAbility.h"
#include "HeroGameplayAbility_TargetLock.generated.h"


class UInputMappingContext;
class UGoliathWidgetBase;

UCLASS()
class GOLIATH_API UHeroGameplayAbility_TargetLock : public UGoliathHeroGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
		bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UFUNCTION(BlueprintCallable)
	void OnTargetLockTick(float DeltaTime);
	
	UFUNCTION(BlueprintCallable)
	void SwitchTarget(const FGameplayTag& InSwitchDirectionTag);
	
private:
	void TryLockOnTarget();
	
	void GetAvailableActorsToLock();
	
	AActor* GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors);
	
	void GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight);
	
	void DrawTargetLockWidget();
	
	void SetTargetLockWidgetPosition();
	
	void InitTargetLockMovement();
	
	void InitTargetLockMappingContext();
	
	void CancelTargetLockAbility();
	
	void CleanUp();
	
	void ResetTargetLockMovement();
	
	void ResetTargetLockMappingContext();
	
	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	float BoxTraceDistance = 5000.f;
	
	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	FVector TraceBoxSize = FVector(2000.f, 2000.f, 300.f);
	
	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	TArray<TEnumAsByte<EObjectTypeQuery>> BoxTraceChannel;
	
	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	bool bShowPersistanceDebugShape = false;
	
	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	TSubclassOf<UGoliathWidgetBase> TargetLockWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	float TargetLockRotationInterpSpeed = 5.f;
	
	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	float TargetLockMaxWalkSpeed = 200.f;
	
	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	TObjectPtr<UInputMappingContext> TargetLockMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = TargetLock)
	float TargetLockCameraOffsetDistance = 20.f;
	
	UPROPERTY()
	TArray<AActor*> AvailableActorsToLock;
	
	UPROPERTY()
	AActor* CurrentLockedActor;
	
	UPROPERTY()
	TObjectPtr<UGoliathWidgetBase> DrawnTargetLockWidget;
	
	UPROPERTY()
	FVector2D TargetLockWidgetSize = FVector2D::ZeroVector;
	
	UPROPERTY()
	float CachedDefaultMaxWalkSpeed = 0.f;
};
