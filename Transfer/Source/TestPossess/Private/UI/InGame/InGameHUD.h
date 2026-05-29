#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"

class UInGameMainWidget;

UCLASS()
class AInGameHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<UInGameMainWidget> mainWidgetClass = nullptr;
	UPROPERTY(VisibleAnywhere) TObjectPtr<UInGameMainWidget> currentMainWidget = nullptr;

public:
	FORCEINLINE UInGameMainWidget* GetMainWidget() { return currentMainWidget; }

private:
	virtual void BeginPlay() override;

};