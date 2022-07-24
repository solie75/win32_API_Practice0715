#include "stdafx.h"
#include "CMissile.h"
#include "CTimeMgr.h"
#include "CEngine.h"
#include "CImage.h"
#include "CResMgr.h"

CMissile::CMissile()
	: m_MissileSpeed(400.f)
{
}

CMissile::~CMissile()
{
}


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

	//  현재 _dc 의 GDIOBJ 를 변환하는 코드
	tSelectBrush b(_dc, BRUSH_COLOR::GRAY);
	tSelectPen p(_dc, PEN_COLOR::RED);

	//Ellipse(_dc
	//	, (int)(MissilePos.x - MissileScale.x / 2)
	//	, (int)(MissilePos.y - MissileScale.y / 2)
	//	, (int)(MissilePos.x + MissileScale.x / 2)
	//	, (int)(MissilePos.y + MissileScale.y / 2));

	CImage* pImage = CResMgr::GetInst()->FindImg(L"PlayerImage");

	if (nullptr == pImage)
	{
		return;
	}

	Vec vPos = GetPos();
	//BitBlt(_dc, (int)vPos.x - 61, (int)vPos.y - 62, 123, 124, pImage->GetImageDC(), 0, 0, SRCCOPY);
	TransparentBlt(_dc, (int)vPos.x - pImage->GetWidth() / 2, (int)vPos.y - pImage->GetHeight() / 2
		, pImage->GetWidth(), pImage->GetHeight()
		, pImage->GetImageDC(), 0, 0, pImage->GetWidth(), pImage->GetHeight(), RGB(255, 0, 255));

	CObject::ObjRender(_dc);
}
