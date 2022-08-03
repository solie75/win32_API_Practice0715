#include "stdafx.h"
#include "CCollider.h"
#include "CObject.h" // Object�� Pos �� Scale�� �˱� ���� ����
#include "CEngine.h"

CCollider::CCollider()
// CCollider �� �����ڴ� �θ� Ŭ���� CComponent�� �����ڸ� ȣ���Ѵ�.
// �̶� CComponent�� �⺻������ ���� ���ڸ� ������ ������ ���� ���� �ϹǷ� �� ���ڸ� ������ �����ڸ� ��ӹ޴´ٰ� ǥ���Ѵ�.
// ���� �ڵ�� CCollider Ŭ������ �����ڰ� �θ� ũ������ CComponent Ŭ������ �����ڸ� ��� �޾Ҵٴ� ���̴�.
	: CComponent(COMPONENT_TYPE::COLLIDER)
	, m_iCollisionCount(0)
{
}

CCollider::~CCollider()
{
}

void CCollider::ComponentTick()
{
	CObject* pOwnerObject = GetOwnerObject();

	// �浹ü�� ���� ��ġ�� ��ü�� ��ġ + ��ü�� �浹ü ������ �Ÿ��� ����.
	m_ColliderFinalPos = pOwnerObject->GetPos() + m_ColliderOffSet;
}

void CCollider::ComponentRender(HDC _dc)
{
	// �浹 Ƚ�� ���� ���� �߻�
	// ���� �浹�� ���� ���� �ʾҴµ� �浹 Ƚ���� �ö� ������ ����
	//assert(0 <= m_iCollisionCount);

	// ��Ȳ�� ���� ���� �ٸ��� ����Ǿ�� �ϹǷ� HDC �� ���ڷ� �޴� tSelectPen �� �ʿ�
	tSelectPen ColliderPen(_dc);
	if (0 < m_iCollisionCount)
	{
		// �浹�� ���
		ColliderPen.SetPenColor(PEN_COLOR::RED);
	}
	else
	{
		// �浹���� ���� ���
		ColliderPen.SetPenColor(PEN_COLOR::GREEN);
	}

	tSelectBrush ColliderBrush(_dc, BRUSH_COLOR::HOLLOW);

	Vec vPos = CCameraMgr::GetInst()->GetRenderPos(m_ColliderFinalPos);

	Rectangle(_dc, (int)(vPos.x - m_ColliderScale.x / 2.f)
		, (int)(vPos.y - m_ColliderScale.y / 2.f)
		, (int)(vPos.x + m_ColliderScale.x / 2.f)
		, (int)(vPos.y + m_ColliderScale.y / 2.f));
}

// �浹 ����
void CCollider::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	++m_iCollisionCount;

	GetOwnerObject()->CollisionBeginOverlap(_pOtherCollider);
}

// �浹 ��
void CCollider::CollisionOverlap(CCollider* _pOtherCollider)
{
	GetOwnerObject()->CollisionOverlap(_pOtherCollider);
}


// �浹 ����
void CCollider::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	--m_iCollisionCount;

	GetOwnerObject()->CollisionEndOverlap(_pOtherCollider);
} 
