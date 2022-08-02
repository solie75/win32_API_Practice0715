#pragma once
#include "CEntity.h"
#include "CCameraMgr.h"

class CComponent;
class CCollider;

class CObject
	: public CEntity
{
private:

	// 각 객체는 컴포넌트의 배열을 가지고 있는다.
	CComponent* m_arrComponent[(UINT)COMPONENT_TYPE::END];

	Vec m_vPos;
	Vec m_vScale;

	bool m_DeadState; // 현재 객체가 죽어있는지 아닌지

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

	// 충돌이벤트
	virtual void CollisionBeginOverlap(CCollider* _pOhterCollider) {};
	virtual void CollisionOverlap(CCollider* _pOhterCollider) {};
	virtual void CollisionEndOverlap(CCollider* _pOhterCollider) {};

public:
	// 순수 가상함수로 사용하던 Tick() 을 CObject 에서 사용해야 함에 따라 대체할 순수가상 함수를 임시로 만듦
	// 순수 가상함수가 존재 해야 하는 이유 -> CObject 클래스로는 객체를 만들 수 없다.
	virtual CObject* Clone() = 0;

private:
	void SetDead() { m_DeadState = true; }

	friend class CEventMgr;

public:
	CObject();
	virtual ~CObject();
};

