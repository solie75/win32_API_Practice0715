#include "stdafx.h"
#include "CObject.h"

void CObject::ObjRender(HDC _dc)
{
	Rectangle(_dc
		, int(m_vPos.x - m_vScale.x / 2.f)
		, int(m_vPos.y - m_vScale.y / 2.f)
		, int(m_vPos.x + m_vScale.x / 2.f)
		, int(m_vPos.y + m_vScale.y / 2.f));
}

CObject::CObject()
{
}

CObject::~CObject()
{
}
