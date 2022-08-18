#include "stdafx.h"
#include "CForce.h"
#include "CTimeMgr.h"
#include "CScene.h"
#include "CSceneMgr.h"

#include "CRigidBody.h"

CForce::CForce()
	: m_fForce(0.f)
	, m_fRadius(0.f)
	, m_fDuration(0.f)
	, m_fAccTime(0.f)
{
}

CForce::~CForce()
{
}

void CForce::ObjTick()
{
	m_fAccTime += DT;

	if (m_fDuration <= m_fAccTime)
	{
		DeleteObject(this);
		return;
	}

	Vec vForcePos = GetPos();

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecObj = pCurScene->GetObjects(LAYER_TYPE::PLAYER);

	for (size_t i = 0; i < vecObj.size(); ++i)
	{
		/*if (vForcePos.Distance(vecObj[i]->GetPos() ) < m_fRadius)
		{ 
			continue;
		}*/
		// ����� �Ǵ� ������Ʈ�� ������ �������� �ʰų� �Ÿ��� �ְų� �ϸ� �ǳ� �ڴ�.
		if (!vecObj[i]->GetRigidBody() || vForcePos.Distance(vecObj[i]->GetPos()) > m_fRadius)
		{
			continue;
		}

		Vec vForce = (vecObj[i]->GetPos() - vForcePos).Normalize() * m_fForce;
		vecObj[i]->GetRigidBody()->AddForce(vForce);
	}
}

void CForce::ObjRender(HDC _dc)
{
	tSelectPen pen(_dc, PEN_COLOR::BLUE);
	tSelectBrush brush(_dc, BRUSH_COLOR::HOLLOW);

	Vec vPos = CCameraMgr::GetInst()->GetRenderPos(GetPos());

	// �� �����Ӹ��� ���� Ŀ����.
	float fRatio = m_fAccTime / m_fDuration;  // ���� ����ð��� ���� (������ �ð��� �� �ۼ�Ʈ ����Ǿ�����)
	float fRadius = m_fRadius * fRatio; // ���� �������� ������ ��( ����ð��� ������(�������� �� �ȵ�����) ���� ���� ���̴�)

	Ellipse(_dc
		, (int)(vPos.x - fRadius)
		, (int)(vPos.y - fRadius)
		, (int)(vPos.x + fRadius)
		, (int)(vPos.y + fRadius));
}
