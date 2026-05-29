#include "Subsystem/CloneSubsystem.h"
#include "Player/RedCharacter.h"

void UCloneSubsystem::RegisterClone(ARedCharacter* _clone)
{
	if(_clone)
		allClones.Add(_clone);
}

void UCloneSubsystem::RemoveClone(ARedCharacter* _clone)
{
	if (!_clone) return;

	int _count = allClones.Num();
	for (int _i = 0; _i < _count; _i++)
	{
		if (allClones[_i] == _clone)
		{
			allClones.RemoveAt(_i, EAllowShrinking::Yes);
			_clone->Destroy();
			break;
		}
	}
}

void UCloneSubsystem::DestroyAllClones()
{
	int _count = allClones.Num();
	for (int _i = 0; _i < _count; _i++)
	{
		if (allClones[_i])
			allClones[_i]->Destroy();
	}
	allClones.Empty();
}