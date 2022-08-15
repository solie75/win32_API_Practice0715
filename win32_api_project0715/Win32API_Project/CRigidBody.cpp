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

	// 속도에 가속도를 더한다.
	m_vVelocity += m_vAccel * DT;

	// 속도에 맞게 물체를 이동시킨다.
	Vec vPos = GetOwnerObject()->GetPos() + m_vVelocity * DT;
	GetOwnerObject()->SetPos(vPos);

	m_vForce = Vec(0.f, 0.f);
}