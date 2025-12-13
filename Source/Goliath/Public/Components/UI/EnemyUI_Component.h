// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "PawnUI_Component.h"
#include "EnemyUI_Component.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GOLIATH_API UEnemyUI_Component : public UPawnUI_Component
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnemyUI_Component();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
