#include "stdafx.h"
#include "CObject.h"
#include "CComponent.h"

// 객체가 새롭게 컴포넌트를 생성하면 기존의 객체가 가지고 있던 컴포넌트 배열에 컬라이더 컴포넌트를 넣는다.
void CObject::AddComponent(CComponent* _pComponent)
{
	//m_arrComponent[(UINT)COMPONENT_TYPE::COLLIDER] = _pComponent;
	m_arrComponent[(UINT)_pComponent->GetComponentType()] = _pComponent;
}

void CObject::ObjTick()
{
	// CObject의 Tick 이 객체가 가진 모든 Component의 Tick 을 호출한다.
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == m_arrComponent[i])
		{
			// 반복문에서 continue 는 그 밑의 나머지 구문을 무시하고 조건문을 이어서 실행한다.
			// break 는 반복문을 종료한다.
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
