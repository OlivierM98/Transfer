#include "UI/InGame/CooldownWidget.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"

void UCooldownWidget::NativeConstruct()
{
	Super::NativeConstruct();
	StopCooldown();
}

void UCooldownWidget::NativeTick(const FGeometry& Geo, float DeltaTime)
{
	Super::NativeTick(Geo, DeltaTime);

	if (isActive && !UGameplayStatics::IsGamePaused(GetWorld()))
		UpdateCooldown(DeltaTime);
}

void UCooldownWidget::ActivateCooldown()
{
	isActive = true;
}

void UCooldownWidget::StopCooldown()
{
	isActive = false;
	currentTime = 0.0f;
}

void UCooldownWidget::UpdateCooldown(float _deltaTime)
{
	currentTime += _deltaTime;
	cooldownBar->SetPercent(1.0f - (currentTime / activeTime));
	if (cooldownBar->GetPercent() <= 0.0f)
	{
		onCooldownFinished.Broadcast();
		StopCooldown();
	}
}