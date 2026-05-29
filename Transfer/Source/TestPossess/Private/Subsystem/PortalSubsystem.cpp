#include "Subsystem/PortalSubsystem.h"
#include "GPE/Portal.h"

void UPortalSubsystem::AddPortal(APortal* _portal)
{
	if (!_portal) return;

	if (portals.Num() >= 2)
	{
		if (flipFlop)
		{
			portals[0]->Destroy();
			portals[0] = _portal;
		}
		else
		{
			portals[1]->Destroy();
			portals[1] = _portal;
		}		
	}
	else
		portals.Add(_portal);

	if (portals.Num() >= 2)
	{
		portals[0]->SetPortalConnected(portals[1]);
		portals[1]->SetPortalConnected(portals[0]);
	}

	flipFlop = !flipFlop;
}

void UPortalSubsystem::DestroyAllPortals()
{
	for (int _i = 0; _i < portals.Num(); _i++)
	{
		if (portals[_i])
			portals[_i]->Destroy();
	}
	portals.Empty();

	flipFlop = true;
}