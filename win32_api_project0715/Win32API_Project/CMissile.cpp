#include "stdafx.h"
#include "CMissile.h"

#include "CEngine.h"
#include "CTimeMgr.h"

#include "CResMgr.h"
#include "CImage.h"
#include "CCollider.h"

CMissile::CMissile()
	: m_MissileSpeed(400.f)
	, m_MissileImage(nullptr)
	, m_fDir(0.f)
{
	m_MissileImage = CResMgr::GetInst()->LoadImg(L"Missile", L"image\\missile.bmp");

	AddComponent(new CCollider);
	GetCollider()->SetColliderScale(Vec(10.f, 30.f));
	GetCollider()->SetColliderOffset(Vec(0.f, -10.f));
}

CMissile::~CMissile()
{
}


void CMissile::ObjTick()
{
	//// 방향 회전
	//m_vDir = RotateVector(m_vDir, -90.f * DT);


	// 미사일이 향하는 방향으로 이동한다.
	Vec MissilePos = GetPos();

	//MissilePos.y -= m_MissileSpeed * DT;
	// 삼각함수를 이용한 이동
	/*MissilePos.x += m_MissileSpeed * cosf(m_fDir) * DT;
	MissilePos.y -= m_MissileSpeed * sinf(m_fDir) * DT;*/

	// 벡터를 이용한 이동
	// 벡터의 정규화를 통해서 길이를 1로 만들었기 때문데 m_MissileSpeed 를 곱하면 최종적으로 갈 거리가 되고
	// 거기에 DT 를 곱하면 한 프레임에 가야할 거리가 된다.
	// 삼각비 이용
	MissilePos.x += m_vDir.x* m_MissileSpeed* DT;
	MissilePos.y += m_vDir.y* m_MissileSpeed* DT; // 삼각함수와 다르게 음수로 바꿀 필요가 없다.

	SetPos(MissilePos);
	
	CObject::ObjTick();
}

void CMissile::ObjRender(HDC _dc)
{
	// 미사일 진행 방향에 따른 인덱스 계산
	UINT iWidth = m_MissileImage->GetWidth() / 8;
	// 8가지의 방향으로 미사일을 쏜다고 할때
	// 위쪽을 향하는 벡터와 내가 나아가는 벡터의 내적을 기준으로 방향을 정한다.
	float fDot = m_vDir.Dot(Vec(0.f, -1.f));
	float fAngle = acosf(fDot);

	// 각도가 180을 넘을 때 보정( 양의 각도(작은 쪾)로만 나오므로 더 큰 쪽 각도를 구하기 위함)
	if (m_vDir.x < 0.f)
	{
		fAngle = PI * 2 - fAngle;
	}

	fAngle += PI / 8.f;

	// 인덱스가 0~7을 넘어서 한바퀴 넘는 경우 다시 0으로
	int iImgIdx = (int)floor(fAngle / (PI / 4.f));
	if (iImgIdx >= 8)
	{
		iImgIdx = 0;
	}

	//Vec MissilePos = GetPos();
	Vec MissilePos = CCameraMgr::GetInst()->GetRenderPos(GetPos());
	//Vec MissileScale = GetScale();

	//  현재 _dc 의 GDIOBJ 를 변환하는 코드
	/*tSelectBrush b(_dc, BRUSH_COLOR::GRAY);
	tSelectPen p(_dc, PEN_COLOR::RED);*/

	//Vec vPos = GetPos();
	//BitBlt(_dc, (int)vPos.x - 61, (int)vPos.y - 62, 123, 124, pImage->GetImageDC(), 0, 0, SRCCOPY);

	TransparentBlt(_dc
		, (int)MissilePos.x - iWidth / 2
		, (int)MissilePos.y - m_MissileImage->GetHeight() / 2
		, iWidth
		, m_MissileImage->GetHeight()
		, m_MissileImage->GetImageDC()
		, iImgIdx * iWidth
		, 0
		, iWidth
		, m_MissileImage->GetHeight()
		, RGB(255, 0, 255));
	
	CObject::ObjRender(_dc);
}
