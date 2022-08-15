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
	//// ���� ȸ��
	//m_vDir = RotateVector(m_vDir, -90.f * DT);


	// �̻����� ���ϴ� �������� �̵��Ѵ�.
	Vec MissilePos = GetPos();

	//MissilePos.y -= m_MissileSpeed * DT;
	// �ﰢ�Լ��� �̿��� �̵�
	/*MissilePos.x += m_MissileSpeed * cosf(m_fDir) * DT;
	MissilePos.y -= m_MissileSpeed * sinf(m_fDir) * DT;*/

	// ���͸� �̿��� �̵�
	// ������ ����ȭ�� ���ؼ� ���̸� 1�� ������� ������ m_MissileSpeed �� ���ϸ� ���������� �� �Ÿ��� �ǰ�
	// �ű⿡ DT �� ���ϸ� �� �����ӿ� ������ �Ÿ��� �ȴ�.
	// �ﰢ�� �̿�
	MissilePos.x += m_vDir.x* m_MissileSpeed* DT;
	MissilePos.y += m_vDir.y* m_MissileSpeed* DT; // �ﰢ�Լ��� �ٸ��� ������ �ٲ� �ʿ䰡 ����.

	SetPos(MissilePos);
	
	CObject::ObjTick();
}

void CMissile::ObjRender(HDC _dc)
{
	// �̻��� ���� ���⿡ ���� �ε��� ���
	UINT iWidth = m_MissileImage->GetWidth() / 8;
	// 8������ �������� �̻����� ��ٰ� �Ҷ�
	// ������ ���ϴ� ���Ϳ� ���� ���ư��� ������ ������ �������� ������ ���Ѵ�.
	float fDot = m_vDir.Dot(Vec(0.f, -1.f));
	float fAngle = acosf(fDot);

	// ������ 180�� ���� �� ����( ���� ����(���� �U)�θ� �����Ƿ� �� ū �� ������ ���ϱ� ����)
	if (m_vDir.x < 0.f)
	{
		fAngle = PI * 2 - fAngle;
	}

	fAngle += PI / 8.f;

	// �ε����� 0~7�� �Ѿ �ѹ��� �Ѵ� ��� �ٽ� 0����
	int iImgIdx = (int)floor(fAngle / (PI / 4.f));
	if (iImgIdx >= 8)
	{
		iImgIdx = 0;
	}

	//Vec MissilePos = GetPos();
	Vec MissilePos = CCameraMgr::GetInst()->GetRenderPos(GetPos());
	//Vec MissileScale = GetScale();

	//  ���� _dc �� GDIOBJ �� ��ȯ�ϴ� �ڵ�
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
