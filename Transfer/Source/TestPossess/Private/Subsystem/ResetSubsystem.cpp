#include "Subsystem/ResetSubsystem.h"
#include "ResetableInterface.h"

void UResetSubsystem::Register(TScriptInterface<IResetableInterface> _resetable)
{
	if (_resetable)
	{
		if (!allResetables.Contains(_resetable))
			allResetables.Add(_resetable);
	}
}

void UResetSubsystem::ResetAll()
{
	int _count = allResetables.Num();
	for (int _i = 0; _i < _count; _i++)
	{
		IResetableInterface* _reset = allResetables[_i].GetInterface();
		if (_reset)
			_reset->Reset();
	}
}