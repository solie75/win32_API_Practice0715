#include "stdafx.h"
#include "func.h"

void DeleteObject(CObject* _pObj)
{
	tEventInfo info = {};
	info.eType = EVENT_TYPE::DELETE_OBJECT;
	info.first = (DWORD_PTR)_pObj;
	CEventMgr::GetInst()->AddEvent(info);
}

Vec RotateVector(Vec _vOrigin, float _Degree)
{
	float fRadian = (_Degree / 180.f) * PI; //회전하고 싶은 각도를 radian화 한것

	_vOrigin.Normalize();



	return Vec(cosf(fRadian) * _vOrigin.x - sinf(fRadian) * _vOrigin.y
		, sinf(fRadian) * _vOrigin.x + cosf(fRadian) * _vOrigin.y);
}

float CrossVector(Vec _v1, Vec _v2) // 외적을 구하는 함수
{
	return _v1.x * _v2.y - _v1.y * _v2.x;
}
