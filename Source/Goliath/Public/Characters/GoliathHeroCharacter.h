// Midnight Madness, Inc.

#pragma once

#include "CoreMinimal.h"
#include "GoliathBaseCharacter.h"
#include "GoliathHeroCharacter.generated.h"

class UDataAsset_InputConfig;
class UCameraComponent;
class USpringArmComponent;

struct FInputActionValue;

UCLASS()
class GOLIATH_API AGoliathHeroCharacter : public AGoliathBaseCharacter
{
	GENERATED_BODY()

public:
	AGoliathHeroCharacter();

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void BeginPlay() override;

private:
	void Input_Move(const FInputActionValue& InputActionValue);
	
	void Input_Look(const FInputActionValue& InputActionValue);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = CharacterData, meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataAsset_InputConfig> InputConfigDataAsset;
};
