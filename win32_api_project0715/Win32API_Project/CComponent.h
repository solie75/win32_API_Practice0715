#pragma once
#include "CEntity.h"

class CObject;

class CComponent
	: public CEntity
{
private:

	// AddComponent �� ���ؼ� ������Ʈ�� ������ ��
	// �� ������Ʈ�� �ڽ��� ��� ������Ʈ ���� �����ϴ� ������ ���ؼ� ������Ʈ Ÿ���� ����� �����Ѵ�.
	// �̶� ����� ������ �ɹ� ����� �ʱ�ȭ �� �ϸ� ���̻� ������ ������ �������� �ʱ�ȭ�θ� (����x) ���� �ִ� ���� �����ϴ�.
	const COMPONENT_TYPE m_eType;
	CObject* m_pOwner; // �ڽ��� � ��ü�� �����ִ��� �˱� ���� ��ü�� �����͸� ���´�.( ��ü�� ������Ʈ�� ���� �˰� �־�� �ֹ濡�� ����)

public:
	virtual void ComponentTick() = 0;
	virtual void ComponentRender(HDC _dc) {};

	COMPONENT_TYPE GetComponentType() { return m_eType; };

	CObject* GetOwnerObject() { return m_pOwner; }

public:
	// �����ڴ� ����ڰ� ������ ��� �⺻�����ڰ� �������� �ʴ´�.
	// new CComponent �� ������Ʈ�� ������ �� �� ������Ʈ�� ������ ���ڷ� �־ ��� ������ �ʱ�ȭ �ϰ� �����μ�
	// �� ������Ʈ�� ���� ������ �ǰ� �Ѵ�.
	CComponent(COMPONENT_TYPE _eType)
		: m_eType(_eType)
		, m_pOwner(nullptr)
	{};
	~CComponent(){};

	// CObject �ɹ� �������� CComponent�� private �� ���� �� ����������.
	friend class CObject;
};

