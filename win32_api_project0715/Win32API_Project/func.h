#pragma once

template<typename T>
bool IsValid(T*& _pPtr)
{
	if (_pPtr->IsDead())
	{
		_pPtr = nullptr;
		return false;
	}

	return true;
}

