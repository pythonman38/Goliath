// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoliathWeaponBase.generated.h"

class UBoxComponent;

UCLASS()
class GOLIATH_API AGoliathWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AGoliathWeaponBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapons)
	TObjectPtr<UStaticMeshComponent> WeaponMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapons)
	TObjectPtr<UBoxComponent> WeaponCollisionBox;
	
public:
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }
};
