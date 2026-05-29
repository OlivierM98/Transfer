#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <InputAction.h>
#include "PossessComponent.generated.h"

class APlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPossessComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TEnumAsByte<ETraceTypeQuery> possessLayout;

	UPROPERTY() TObjectPtr<APlayerCharacter> owner = nullptr;

	// ===== Debug ===========
	UPROPERTY(EditAnywhere, Category = "Debug") bool useDebug = true;
	UPROPERTY(EditAnywhere, Category = "Debug") float radius = 50.0f;

public:	
	UPossessComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION() void TryPossess(const FInputActionValue& _value);
	UFUNCTION() void CancelPossess();

};