#include "stdafx.h"
#include "CMissile.h"
#include "CTimeMgr.h"

void CMissile::ObjTick()
{
	Vec MissilePos = GetPos();

	MissilePos.y -= m_MissileSpeed * DT;

	SetPos(MissilePos);
}

void CMissile::ObjRender(HDC _dc)
{
	Vec MissilePos = GetPos();
	Vec MissileScale = GetScale();

	Ellipse(_dc
		, (int)MissilePos.x - MissileScale.x / 2
		, (int)MissilePos.y - MissileScale.y / 2
		, (int)MissilePos.x + MissileScale.x / 2
		, (int)MissilePos.y + MissileScale.y / 2);
}

CMissile::CMissile()
	: m_MissileSpeed(400.f)
{
}

CMissile::~CMissile()
{
}
