#pragma once

class CComponent;
class CCollider;

class CObject
{
private:

	// 각 객체는 컴포넌트의 배열을 가지고 있는다.
	CComponent* m_arrComponent[(UINT)COMPONENT_TYPE::END];

	Vec m_vPos;
	Vec m_vScale;

public:
	void SetPos(Vec _vPos)
	{
		m_vPos = _vPos;
	}
	void SetScale(Vec _vScale)
	{
		m_vScale = _vScale;
	}

	Vec GetPos()
	{
		return m_vPos;
	}
	Vec GetScale()
	{
		return m_vScale;
	} 

	CCollider* GetCollider() { return (CCollider*)m_arrComponent[(UINT)COMPONENT_TYPE::COLLIDER]; }
	//CAnimator* GetAnimator() { return (CCollider*)m_arrComponent[(UINT)COMPONENT_TYPE::ANIMATOR]; }
	//CGravity* GetGravity() { return (CCollider*)m_arrComponent[(UINT)COMPONENT_TYPE::GRAVITY]; }

	void AddComponent(CComponent* _pComponent);
	

	virtual void ObjTick();
	virtual void ObjRender(HDC _dc);

public:
	// 순수 가상함수로 사용하던 Tick() 을 CObject 에서 사용해야 함에 따라 대체할 순수가상 함수를 임시로 만듦
	// 순수 가상함수가 존재 해야 하는 이유 -> CObject 클래스로는 객체를 만들 수 없다.
	virtual CObject* Clone() = 0;

public:
	CObject();
	~CObject();
};

