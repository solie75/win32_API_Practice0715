#include "stdafx.h"
#include "CGuidedMissile.h"

#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "CMonster.h"
#include "CCollider.h"

CGuidedMissile::CGuidedMissile()
	: m_pTarget(nullptr)
	, m_fRotateSpeed(180.f)
	, m_fDetectRange(1000.f)
{
}

CGuidedMissile::~CGuidedMissile()
{
}


void CGuidedMissile::FindTarget()
{
	if (IsValid(m_pTarget))
	{
		return;
	}
	
	Vec vMissilePos = GetPos();

	// 현재 Scene을 찾는다.
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// Monster layer 를 가져온다.
	const vector<CObject*>& vecMon = pCurScene->GetObjects(LAYER_TYPE::MONSTER);
	
	float fDistance = m_fDetectRange; // 두 객체 사이의 거리, 탐지 반경
	// 1000 이내의 다른 타겟 객체가 존재 하지 않다면 직진한다.
	for (size_t i = 0; i < vecMon.size(); ++i)
	{
		float fDist = vMissilePos.Distance(vecMon[i]->GetPos()); // 탐지 대상과 this 간의 거리

		if (fDist < fDistance)
		{
			fDistance = fDist; 
			// 결과 적으로 fDistance 에는 초기값 내에 목표객체가 있다는 가정하에 유도탄 미사일과 가장가까운 객체와의 거리를 가진다.
			m_pTarget = vecMon[i];
		}
	}
	
}

void CGuidedMissile::ObjTick()
{
	// 타겟을 찾는다.
	FindTarget();

	// 타겟을 향하여 방향을 회전
	if (nullptr != m_pTarget) // 타겟이 존재한다면
	{
		// SetDir(m_pTarget->GetPos() - GetPos()); // 목표 객체의 위치에서 유도 미사일의 위치를 뺀값을 벡터화 한다.
		// 타겟을 향해서 방향을 회전한다.
		Vec vMonPos = m_pTarget->GetPos(); // 타겟의 위치 정보
		Vec vMissilePos = GetPos(); // 미사일(this)의 위치 정보

		Vec vDirToMon = vMonPos - vMissilePos;  // 타겟에 대한 this의 벡터
		Vec vMissileDir = GetDir(); // 단위 벡터로 정리되어 있는 this의 백터를 가져온다.(이사일이 원래 나아가고자 하는 방향에 대한 벡터)

		vDirToMon.Normalize();
		vMissileDir.Normalize(); // 단위 벡터화가 안되어 있는 경우를 대비하여

		float fDot = vMissileDir.Dot(vDirToMon); // 미사일의 원래 벡터와 카겟에 대한 벡터의 내적
		float fAngle = acosf(fDot); 
		// 미사일의 진행방향과 몬스터를 향하는 방향 사이의 각도를 구한다.(역함수 개념 이용)
		fAngle = (fAngle / PI) * 180.f; // Radian to Degree
		
		float fRotateAngle = m_fRotateSpeed * DT; // 회전 각도 크기

		// 이때 마사일의 회전 각도 크기는 이 fAngle 보다 작아야 한다.
		if (fAngle < fRotateAngle)
		{
			fRotateAngle = fAngle;
		}
		// 회전할 방향 정하기
		if (0.f < CrossVector(vDirToMon, vMissileDir))
		{
			fRotateAngle *= -1.f;
		}

		vMissileDir = RotateVector(vMissileDir, fRotateAngle);
		SetDir(vMissileDir);
	}

	CMissile::ObjTick();
}

void CGuidedMissile::ObjRender(HDC _dc)
{
	CMissile::ObjRender(_dc);
}

void CGuidedMissile::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	if (dynamic_cast<CMonster*>(_pOtherCollider->GetOwnerObject()))
	{
		DeleteObject(this);
	}
}
