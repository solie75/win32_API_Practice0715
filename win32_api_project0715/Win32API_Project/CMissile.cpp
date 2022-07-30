#include "stdafx.h"
#include "CMissile.h"

#include "CEngine.h"
#include "CTimeMgr.h"

#include "CResMgr.h"
#include "CImage.h"
#include "CCollider.h"

CMissile::CMissile()
	: m_MissileSpeed(400.f)
	, MissileImage(nullptr)
{
	MissileImage = CResMgr::GetInst()->LoadImg(L"Missile", L"image\\missile.bmp");

	AddComponent(new CCollider);
	GetCollider()->SetColliderScale(Vec(10.f, 30.f));
	GetCollider()->SetColliderOffset(Vec(0.f, -10.f));
}

CMissile::~CMissile()
{
}


void CMissile::ObjTick()
{
	Vec MissilePos = GetPos();

	MissilePos.y -= m_MissileSpeed * DT;

	SetPos(MissilePos);
	
	CObject::ObjTick();
}

void CMissile::ObjRender(HDC _dc)
{
	//Vec MissilePos = GetPos();
	Vec MissilePos = CCameraMgr::GetInst()->GetRenderPos(GetPos());
	//Vec MissileScale = GetScale();

	//  현재 _dc 의 GDIOBJ 를 변환하는 코드
	/*tSelectBrush b(_dc, BRUSH_COLOR::GRAY);
	tSelectPen p(_dc, PEN_COLOR::RED);*/

	//Vec vPos = GetPos();
	//BitBlt(_dc, (int)vPos.x - 61, (int)vPos.y - 62, 123, 124, pImage->GetImageDC(), 0, 0, SRCCOPY);

	TransparentBlt(_dc, (int)MissilePos.x -( MissileImage->GetWidth() / 2), (int)MissilePos.y - (MissileImage->GetHeight() / 2)
		, MissileImage->GetWidth(), MissileImage->GetHeight()
		, MissileImage->GetImageDC(), 0, 0, MissileImage->GetWidth(), MissileImage->GetHeight(), RGB(255, 0, 255));
	
	CObject::ObjRender(_dc);
}
