#include "stdafx.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"
#include "CObject.h"


CRigidBody::CRigidBody()
	: CComponent(COMPONENT_TYPE::RIGIDBODY)
	, m_fMass(1.f)
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

	// �ӵ��� �°� ��ü�� �̵���Ų��.
	Vec vPos = GetOwnerObject()->GetPos() + m_vVelocity * DT;
	GetOwnerObject()->SetPos(vPos);

	m_vForce = Vec(0.f, 0.f);
}