// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GoliathBaseCharacter.h"
#include "GoliathEnemyCharacter.generated.h"

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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
	TObjectPtr<UEnemyCombatComponent> EnemyCombatComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	TObjectPtr<UEnemyUI_Component> EnemyUI_Component;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	TObjectPtr<UWidgetComponent> EnemyHealthWidgetComponent;
	
private:
	void InitEnemyStartUpData();
	
public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() { return EnemyCombatComponent; }
};
