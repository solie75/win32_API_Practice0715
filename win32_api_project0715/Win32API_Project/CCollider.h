#pragma once
#include "CComponent.h"

union COLLIDER_ID
{
	struct
	{ 
		UINT FIRST_ID;
		UINT SECOND_ID;
	};
	LONGLONG ID;
};

class CCollider :
	public CComponent
{
public:
	Vec m_ColliderOffSet; // Object로 부터 상대적인 거리
	Vec m_ColliderScale;

	Vec m_ColliderFinalPos; // 충돌체의 최종 위치

	size_t m_iCollisionCount; // 충돌 횟수

public:
	void SetColliderScale(Vec _vScale) { m_ColliderScale = _vScale; };
	void SetColliderOffset(Vec _vOffset) { m_ColliderOffSet = _vOffset; };

	Vec GetColliderFinalPos() { return m_ColliderFinalPos; }
	Vec GetColliderScale() { return m_ColliderScale; }

public:
	// 충돌이 처음 발생하는 시점
	void CollisionBeginOverlap(CCollider* _pOtherCollider);

	// 충돌 도중
	void CollisionOverlap(CCollider* _pOtherCollider);

	// 충돌이 벗어나지는 지점
	void CollisionEndOverlap(CCollider* _pOtherCollider);

public:
	virtual void ComponentTick() override;
	virtual void ComponentRender(HDC _dc) override;
public:
	CCollider();
	~CCollider();
};

