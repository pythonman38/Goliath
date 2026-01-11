// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "PawnUI_Component.h"
#include "EnemyUI_Component.generated.h"


class UGoliathWidgetBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GOLIATH_API UEnemyUI_Component : public UPawnUI_Component
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawnWidget(UGoliathWidgetBase* InWidgetToRegister);
	
	UFUNCTION(BlueprintCallable)
	void RemoveEnemyDrawnWidgetsIfAny();
	
private:
	TArray<UGoliathWidgetBase*> EnemyDrawnWidgets; 
};
