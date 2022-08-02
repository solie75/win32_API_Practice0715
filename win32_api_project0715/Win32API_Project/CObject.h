#pragma once
#include "CEntity.h"
#include "CCameraMgr.h"

class CComponent;
class CCollider;

class CObject
	: public CEntity
{
private:

	// �� ��ü�� ������Ʈ�� �迭�� ������ �ִ´�.
	CComponent* m_arrComponent[(UINT)COMPONENT_TYPE::END];

	Vec m_vPos;
	Vec m_vScale;

	bool m_DeadState; // ���� ��ü�� �׾��ִ��� �ƴ���

public:
	void SetPos(Vec _vPos)
	{
		m_vPos = _vPos;
	}
	void SetScale(Vec _vScale)
	{
		m_vScale = _vScale;
	}

	Vec GetPos() const
	{
		return m_vPos;
	}
	Vec GetScale() const
	{
		return m_vScale;
	}

	bool IsDead() const { return m_DeadState; }

	CCollider* GetCollider() const { return (CCollider*)m_arrComponent[(UINT)COMPONENT_TYPE::COLLIDER]; }
	//CAnimator* GetAnimator() { return (CCollider*)m_arrComponent[(UINT)COMPONENT_TYPE::ANIMATOR]; }
	//CGravity* GetGravity() { return (CCollider*)m_arrComponent[(UINT)COMPONENT_TYPE::GRAVITY]; }

	void AddComponent(CComponent* _pComponent);
	

	virtual void ObjTick();
	virtual void ObjRender(HDC _dc);

	// �浹�̺�Ʈ
	virtual void CollisionBeginOverlap(CCollider* _pOhterCollider) {};
	virtual void CollisionOverlap(CCollider* _pOhterCollider) {};
	virtual void CollisionEndOverlap(CCollider* _pOhterCollider) {};

public:
	// ���� �����Լ��� ����ϴ� Tick() �� CObject ���� ����ؾ� �Կ� ���� ��ü�� �������� �Լ��� �ӽ÷� ����
	// ���� �����Լ��� ���� �ؾ� �ϴ� ���� -> CObject Ŭ�����δ� ��ü�� ���� �� ����.
	virtual CObject* Clone() = 0;

private:
	void SetDead() { m_DeadState = true; }

	friend class CEventMgr;

public:
	CObject();
	virtual ~CObject();
};

