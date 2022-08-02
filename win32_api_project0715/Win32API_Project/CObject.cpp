#include "stdafx.h"
#include "CObject.h"
#include "CComponent.h"

// 객체가 새롭게 컴포넌트를 생성하면 기존의 객체가 가지고 있던 컴포넌트 배열에 컴포넌트를 넣는다.
void CObject::AddComponent(CComponent* _pComponent)
{
	//m_arrComponent[(UINT)COMPONENT_TYPE::COLLIDER] = _pComponent;
	
	// 컴포넌트 배열에 컴포넌트를 넣는 과정
	/*객체 클래스의 생성자에서 해당 객체가 가지게 될 컴포넌트를 생성
		AddComponent(new ~~);

	동적 할당 받은 컴포넌트는
	1. 자기 자신의 타입을 뜻하는 상수 값을 가진다. const COMPONENT_TYPE m_eType;
	2. 자신이 어떤 객체에 속해 있는지 알기 위해 객체의 포인터를 갖는다.m_pOwner;

	동적 할당 받은 컴포넌트의 주소값이
		AddComponent의 매개 변수가된다.*/

	// 새롭게 동적할 다앋은 컴포넌트를 종류에 맞는 컴포넌트 배열의 인덱스에 넣는다.
	m_arrComponent[(UINT)_pComponent->GetComponentType()] = _pComponent;

	// 해당 컴포넌트의 객체를 입력한다.
	_pComponent->m_pOwner = this;
}

void CObject::ObjTick()
{
	// CObject의 Tick 이 객체가 가진 모든 Component의 Tick 을 호출한다.
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == m_arrComponent[i])
		{
			continue;
		}
		m_arrComponent[i]->ComponentTick();
	}
}

void CObject::ObjRender(HDC _dc)
{
	// 틱과 마찬가지로 직접적인 컴포넌트의 랜더링은 각 컴포넌트의 클래스에서 구현하고 CObject 클래스는 각 컴포넌트들의  render 클래스를 호출한다.
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if(nullptr == m_arrComponent[i])
		{
			continue;
		} 
		m_arrComponent[i]->ComponentRender(_dc);
	 }
}

CObject::CObject()
// 처음에 객체가 생성될 때에는 아직 어떠한 컴포넌트를 객체가 가질 지 모르기 때문에 모든 요소를 nullptr로 초기화 한다.
	: m_arrComponent{}
	, m_DeadState(false)
{
}

CObject::~CObject()
{
	// 객체는 컴포넌트의 주솟값을 가지고 있기 때문에 따로 지워주어야 한다.
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		// 다음 구문이 많이 쓰이기 때문에 매크로화 해준다.
		/*if (nullptr != m_arrComponent[i])
		{
			delete m_arrComponent[i];
		}*/
		SAFE_DELETE(m_arrComponent[i]);
	}

}
