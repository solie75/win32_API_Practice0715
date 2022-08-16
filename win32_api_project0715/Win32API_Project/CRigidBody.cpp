#include "stdafx.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"
#include "CObject.h"


CRigidBody::CRigidBody()
	: CComponent(COMPONENT_TYPE::RIGIDBODY)
	, m_fMass(1.f)
	, m_fFriction(100.f)
{
}

CRigidBody::~CRigidBody()
{
}


void CRigidBody::ComponentTick()
{
	// f = m X a
	m_vAccel = m_vForce / m_fMass;

	// �ӵ��� ���ӵ��� ���Ѵ�.
	m_vVelocity += m_vAccel * DT;

	// ������ ���� (����� ���� ����, �ӵ��� 0�� �ƴ� ��) // �����Ǿ� �ִ� ���¿��� ������( �ӵ��� �ݴ� )�� ����ȴٸ� ������ ������ ���̴�.
	//if (m_vForce.IsZero() && !m_vVelocity.IsZero())
	if( !m_vVelocity.IsZero() )
	{
		// �ӵ��� �ݴ�������� �������� �����Ѵ�.
		Vec vFriction = -m_vVelocity; // �ӵ�*(-1)
		vFriction = vFriction.Normalize() * m_fFriction * DT * m_fMass; // ������ ���� ���� * ������ ������ * DT -> �� �����ӿ��� ������ �������� ������ ��
		
		// �������� �ӵ����� Ŀ�� ������ ��������� �ݴ�������� �������� �̷�����°� ����
		if (m_vVelocity.Length() < vFriction.Length())
		{
			m_vVelocity = Vec(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction; // ������ �ӵ��� �������� ���Ѵ�.
		}
	}

	// �ӵ��� �°� ��ü�� �̵���Ų��.
	Vec vPos = GetOwnerObject()->GetPos() + m_vVelocity * DT;
	GetOwnerObject()->SetPos(vPos);

	m_vForce = Vec(0.f, 0.f);
}