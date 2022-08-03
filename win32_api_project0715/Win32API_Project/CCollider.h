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
	Vec m_ColliderOffSet; // Object�� ���� ������� �Ÿ�
	Vec m_ColliderScale;

	Vec m_ColliderFinalPos; // �浹ü�� ���� ��ġ

	size_t m_iCollisionCount; // �浹 Ƚ��

public:
	void SetColliderScale(Vec _vScale) { m_ColliderScale = _vScale; };
	void SetColliderOffset(Vec _vOffset) { m_ColliderOffSet = _vOffset; };

	Vec GetColliderFinalPos() { return m_ColliderFinalPos; }
	Vec GetColliderScale() { return m_ColliderScale; }

public:
	// �浹�� ó�� �߻��ϴ� ����
	void CollisionBeginOverlap(CCollider* _pOtherCollider);

	// �浹 ����
	void CollisionOverlap(CCollider* _pOtherCollider);

	// �浹�� ������� ����
	void CollisionEndOverlap(CCollider* _pOtherCollider);

public:
	virtual void ComponentTick() override;
	virtual void ComponentRender(HDC _dc) override;
public:
	CCollider();
	~CCollider();
};

