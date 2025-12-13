// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GoliathWidgetBase.generated.h"


class UEnemyUI_Component;
class UHeroUI_Component;

UCLASS()
class GOLIATH_API UGoliathWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Hero UI Component Initialized"))
	void BP_OnOwningHeroUI_ComponentInitialized(UHeroUI_Component* OwningHeroUI_Component);
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Enemy UI Component Initialized"))
	void BP_OnOwningEnmeyUI_ComponentInitialized(UEnemyUI_Component* OwningEnemyUI_Component);
	
public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedWidget(AActor* OwningEnemyActor);
};
