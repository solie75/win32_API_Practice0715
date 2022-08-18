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
		// 대상이 되는 오브젝트에 강제가 존재하지 않거나 거리가 멀거나 하면 건너 뛴다.
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

	// 매 프레임마다 원이 커진다.
	float fRatio = m_fAccTime / m_fDuration;  // 현재 진행시간의 비율 (정해진 시간중 몇 퍼센트 진행되었는지)
	float fRadius = m_fRadius * fRatio; // 원의 반지름과 비율의 곱( 진행시간이 적으면(시작한지 얼마 안됐으면) 원이 작을 것이다)

	Ellipse(_dc
		, (int)(vPos.x - fRadius)
		, (int)(vPos.y - fRadius)
		, (int)(vPos.x + fRadius)
		, (int)(vPos.y + fRadius));
}
