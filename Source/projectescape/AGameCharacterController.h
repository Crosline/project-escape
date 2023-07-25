#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "AGameCharacterController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

UCLASS()
class PROJECTESCAPE_API AGameCharacterController : public APlayerController
{
	GENERATED_BODY()
public:
	AGameCharacterController();
	~AGameCharacterController();

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputMappingContext* MovementInputContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* MovementAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* LookAction;
	
protected:
	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	/** Input handlers. */

private:
	void OnMove(const FInputActionValue& actionValue);
	void Move(APawn* controlledPawn, const FVector2D movementVector2D);
	void OnLook(const FInputActionValue& actionValue);
};
