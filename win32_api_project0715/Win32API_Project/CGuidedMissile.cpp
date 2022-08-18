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

	// ���� Scene�� ã�´�.
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// Monster layer �� �����´�.
	const vector<CObject*>& vecMon = pCurScene->GetObjects(LAYER_TYPE::MONSTER);
	
	float fDistance = m_fDetectRange; // �� ��ü ������ �Ÿ�, Ž�� �ݰ�
	// 1000 �̳��� �ٸ� Ÿ�� ��ü�� ���� ���� �ʴٸ� �����Ѵ�.
	for (size_t i = 0; i < vecMon.size(); ++i)
	{
		float fDist = vMissilePos.Distance(vecMon[i]->GetPos()); // Ž�� ���� this ���� �Ÿ�

		if (fDist < fDistance)
		{
			fDistance = fDist; 
			// ��� ������ fDistance ���� �ʱⰪ ���� ��ǥ��ü�� �ִٴ� �����Ͽ� ����ź �̻��ϰ� ���尡��� ��ü���� �Ÿ��� ������.
			m_pTarget = vecMon[i];
		}
	}
	
}

void CGuidedMissile::ObjTick()
{
	// Ÿ���� ã�´�.
	FindTarget();

	// Ÿ���� ���Ͽ� ������ ȸ��
	if (nullptr != m_pTarget) // Ÿ���� �����Ѵٸ�
	{
		// SetDir(m_pTarget->GetPos() - GetPos()); // ��ǥ ��ü�� ��ġ���� ���� �̻����� ��ġ�� ������ ����ȭ �Ѵ�.
		// Ÿ���� ���ؼ� ������ ȸ���Ѵ�.
		Vec vMonPos = m_pTarget->GetPos(); // Ÿ���� ��ġ ����
		Vec vMissilePos = GetPos(); // �̻���(this)�� ��ġ ����

		Vec vDirToMon = vMonPos - vMissilePos;  // Ÿ�ٿ� ���� this�� ����
		Vec vMissileDir = GetDir(); // ���� ���ͷ� �����Ǿ� �ִ� this�� ���͸� �����´�.(�̻����� ���� ���ư����� �ϴ� ���⿡ ���� ����)

		vDirToMon.Normalize();
		vMissileDir.Normalize(); // ���� ����ȭ�� �ȵǾ� �ִ� ��츦 ����Ͽ�

		float fDot = vMissileDir.Dot(vDirToMon); // �̻����� ���� ���Ϳ� ī�ٿ� ���� ������ ����
		float fAngle = acosf(fDot); 
		// �̻����� �������� ���͸� ���ϴ� ���� ������ ������ ���Ѵ�.(���Լ� ���� �̿�)
		fAngle = (fAngle / PI) * 180.f; // Radian to Degree
		
		float fRotateAngle = m_fRotateSpeed * DT; // ȸ�� ���� ũ��

		// �̶� �������� ȸ�� ���� ũ��� �� fAngle ���� �۾ƾ� �Ѵ�.
		if (fAngle < fRotateAngle)
		{
			fRotateAngle = fAngle;
		}
		// ȸ���� ���� ���ϱ�
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
