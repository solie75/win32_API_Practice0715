#pragma once
#include "CComponent.h"

class CCollider :
	public CComponent
{
public:
	Vec m_ColliderOffSet; // Object로 부터 상대적인 거리
	Vec m_ColliderScale;

	Vec m_ColliderFinalPos; // 충돌체의 최종 위치

public:
	void SetColliderScale(Vec _vScale) { m_ColliderScale = _vScale; };
	void SetColliderOffset(Vec _vOffset) { m_ColliderOffSet = _vOffset; };
public:
	virtual void ComponentTick() override;
	virtual void ComponentRender(HDC _dc) override;
public:
	CCollider();
	~CCollider();
};

