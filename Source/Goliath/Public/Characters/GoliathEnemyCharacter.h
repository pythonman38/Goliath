// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GoliathBaseCharacter.h"
#include "GoliathEnemyCharacter.generated.h"

class UBoxComponent;
class UWidgetComponent;
class UEnemyUI_Component;
class UEnemyCombatComponent;

UCLASS()
class GOLIATH_API AGoliathEnemyCharacter : public AGoliathBaseCharacter
{
	GENERATED_BODY()

public:
	AGoliathEnemyCharacter();
	
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	
	virtual UPawnUI_Component* GetPawnUI_Component() const override;
	
	virtual UEnemyUI_Component* GetEnemyUI_Component() const override;

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void BeginPlay() override;
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
		
	UFUNCTION()
	virtual void OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
	TObjectPtr<UEnemyCombatComponent> EnemyCombatComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
	TObjectPtr<UBoxComponent> LeftHandCollisionBox;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Combat)
	FName LeftHandCollisionBoxAttachBoneName;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
	TObjectPtr<UBoxComponent> RightHandCollisionBox;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Combat)
	FName RightHandCollisionBoxAttachBoneName;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	TObjectPtr<UEnemyUI_Component> EnemyUI_Component;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	TObjectPtr<UWidgetComponent> EnemyHealthWidgetComponent;
	
private:
	void InitEnemyStartUpData();
	
public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() { return EnemyCombatComponent; }
	FORCEINLINE UBoxComponent* GetLeftHandCollisionBox() const { return LeftHandCollisionBox; }
	FORCEINLINE UBoxComponent* GetRightHandCollisionBox() const { return RightHandCollisionBox; }
};
