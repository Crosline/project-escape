#include "AGameCharacterController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AGameCharacterController::AGameCharacterController()
{
}

AGameCharacterController::~AGameCharacterController()
{
}

void AGameCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup movement input events
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AGameCharacterController::OnMove);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGameCharacterController::OnLook);
	}
}

void AGameCharacterController::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MovementInputContext, 0);
	}
}

void AGameCharacterController::OnMove(const FInputActionValue& actionValue)
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn == nullptr)
		return;

	const FVector2D movementVector2D = actionValue.Get<FVector2D>();
	// MoveOne(ControlledPawn, movementVector2D);
	Move(ControlledPawn, movementVector2D);
}

void AGameCharacterController::Move(APawn* controlledPawn, const FVector2D movementVector2D)
{
	const FRotator rotation = GetControlRotation();
	const FRotator yawRotation(0.0f, rotation.Yaw, 0.0f);

	const FVector transformRight = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	controlledPawn->AddMovementInput(transformRight, movementVector2D.X);

	const FVector transformForward = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	controlledPawn->AddMovementInput(transformForward, movementVector2D.Y);
}

void AGameCharacterController::OnLook(const FInputActionValue& actionValue)
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn == nullptr)
		return;

	const FVector2D lookAxis = actionValue.Get<FVector2D>();

	UE_LOG(LogTemp, Warning, TEXT("Mouse Axis: %f, %f"), lookAxis.X, lookAxis.Y);
}


