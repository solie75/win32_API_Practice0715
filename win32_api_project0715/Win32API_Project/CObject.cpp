#include "stdafx.h"
#include "CObject.h"
#include "CComponent.h"

// ��ü�� ���Ӱ� ������Ʈ�� �����ϸ� ������ ��ü�� ������ �ִ� ������Ʈ �迭�� ������Ʈ�� �ִ´�.
void CObject::AddComponent(CComponent* _pComponent)
{
	//m_arrComponent[(UINT)COMPONENT_TYPE::COLLIDER] = _pComponent;
	
	// ������Ʈ �迭�� ������Ʈ�� �ִ� ����
	/*��ü Ŭ������ �����ڿ��� �ش� ��ü�� ������ �� ������Ʈ�� ����
		AddComponent(new ~~);

	���� �Ҵ� ���� ������Ʈ��
	1. �ڱ� �ڽ��� Ÿ���� ���ϴ� ��� ���� ������. const COMPONENT_TYPE m_eType;
	2. �ڽ��� � ��ü�� ���� �ִ��� �˱� ���� ��ü�� �����͸� ���´�.m_pOwner;

	���� �Ҵ� ���� ������Ʈ�� �ּҰ���
		AddComponent�� �Ű� �������ȴ�.*/

	// ���Ӱ� ������ �ٝ��� ������Ʈ�� ������ �´� ������Ʈ �迭�� �ε����� �ִ´�.
	m_arrComponent[(UINT)_pComponent->GetComponentType()] = _pComponent;

	// �ش� ������Ʈ�� ��ü�� �Է��Ѵ�.
	_pComponent->m_pOwner = this;
}

void CObject::ObjTick()
{
	// CObject�� Tick �� ��ü�� ���� ��� Component�� Tick �� ȣ���Ѵ�.
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
	// ƽ�� ���������� �������� ������Ʈ�� �������� �� ������Ʈ�� Ŭ�������� �����ϰ� CObject Ŭ������ �� ������Ʈ����  render Ŭ������ ȣ���Ѵ�.
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
// ó���� ��ü�� ������ ������ ���� ��� ������Ʈ�� ��ü�� ���� �� �𸣱� ������ ��� ��Ҹ� nullptr�� �ʱ�ȭ �Ѵ�.
	: m_arrComponent{}
	, m_DeadState(false)
{
}

CObject::~CObject()
{
	// ��ü�� ������Ʈ�� �ּڰ��� ������ �ֱ� ������ ���� �����־�� �Ѵ�.
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		// ���� ������ ���� ���̱� ������ ��ũ��ȭ ���ش�.
		/*if (nullptr != m_arrComponent[i])
		{
			delete m_arrComponent[i];
		}*/
		SAFE_DELETE(m_arrComponent[i]);
	}

}
