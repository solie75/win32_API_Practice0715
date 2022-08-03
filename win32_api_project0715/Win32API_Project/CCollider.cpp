#include "stdafx.h"
#include "CCollider.h"
#include "CObject.h" // Object의 Pos 와 Scale을 알기 위해 선언
#include "CEngine.h"

CCollider::CCollider()
// CCollider 의 생성자는 부모 클라스인 CComponent의 생성자를 호출한다.
// 이때 CComponent는 기본생성자 없이 인자를 가지는 생성자 만이 존재 하므로 그 인자를 가지는 생성자를 상속받는다고 표시한다.
// 밑의 코드는 CCollider 클래스의 생성자가 부모 크래스인 CComponent 클래스의 생성자를 상속 받았다는 것이다.
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

	// 충돌체의 최종 위치는 객체의 위치 + 객체와 충돌체 사이의 거리와 같다.
	m_ColliderFinalPos = pOwnerObject->GetPos() + m_ColliderOffSet;
}

void CCollider::ComponentRender(HDC _dc)
{
	// 충돌 횟수 제어 오류 발생
	// 아직 충돌을 조사 하지 않았는데 충돌 횟수가 올라가 있으면 오류
	//assert(0 <= m_iCollisionCount);

	// 상황에 따라 색이 다르게 적용되어야 하므로 HDC 만 인자로 받는 tSelectPen 이 필요
	tSelectPen ColliderPen(_dc);
	if (0 < m_iCollisionCount)
	{
		// 충돌한 경우
		ColliderPen.SetPenColor(PEN_COLOR::RED);
	}
	else
	{
		// 충돌하지 않은 경우
		ColliderPen.SetPenColor(PEN_COLOR::GREEN);
	}

	tSelectBrush ColliderBrush(_dc, BRUSH_COLOR::HOLLOW);

	Vec vPos = CCameraMgr::GetInst()->GetRenderPos(m_ColliderFinalPos);

	Rectangle(_dc, (int)(vPos.x - m_ColliderScale.x / 2.f)
		, (int)(vPos.y - m_ColliderScale.y / 2.f)
		, (int)(vPos.x + m_ColliderScale.x / 2.f)
		, (int)(vPos.y + m_ColliderScale.y / 2.f));
}

// 충돌 시작
void CCollider::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	++m_iCollisionCount;

	GetOwnerObject()->CollisionBeginOverlap(_pOtherCollider);
}

// 충돌 중
void CCollider::CollisionOverlap(CCollider* _pOtherCollider)
{
	GetOwnerObject()->CollisionOverlap(_pOtherCollider);
}


// 충돌 종료
void CCollider::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	--m_iCollisionCount;

	GetOwnerObject()->CollisionEndOverlap(_pOtherCollider);
} 
