#pragma once

class CObject;

template<typename T>
bool IsValid(T*& _pPtr)
{
	if(nullptr == _pPtr)
	{
		return false;
	}

	if (_pPtr->IsDead())
	{
		_pPtr = nullptr;
		return false;
	}

	return true;
}

template<typename T1, typename T2>
void Safe_Del_Map(const map<T1, T2>& _map)
{
	typename map<T1, T2>::const_iterator iter = _map.cbegin();
	for (iter; iter != _map.cend(); ++iter)
	{
		delete iter->second;
	}
}


// ====================
// Evnet Function
// ====================
#include "CEventMgr.h"

// Ư�� ��ġ�� ��ü�� ������Ű�� �Լ�
template<typename T>
T* Instantiate(Vec _vPos, LAYER_TYPE _type)
{
	T* pObject = new T;
	pObject->SetPos(_vPos);

	tEventInfo info = {};
	info.eType = EVENT_TYPE::CREATE_OBJECT;
	info.first = (DWORD_PTR)pObject;
	info.second = (DWORD_PTR)_type;

	CEventMgr::GetInst()->AddEvent(info);

	return pObject;
}

// ��ü�� �����ϴ� �Լ�
void DeleteObject(CObject* _pObj);

// Angle ����
// Radian  ������
// Degree 60�й�
Vec RotateVector(Vec _vOrigin, float _Degree);

float CrossVector(Vec _v1, Vec _v2);