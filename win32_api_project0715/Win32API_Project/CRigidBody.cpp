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

	// 속도에 가속도를 더한다.
	m_vVelocity += m_vAccel * DT;

	// 마찰력 조건 (적용된 힘이 없고, 속도가 0이 아닐 때) // 정지되어 있는 상태에서 마찰력( 속도의 반대 )가 적용된다면 오히려 움직일 것이다.
	//if (m_vForce.IsZero() && !m_vVelocity.IsZero())
	if( !m_vVelocity.IsZero() )
	{
		// 속도의 반대방향으로 마찰력을 적용한다.
		Vec vFriction = -m_vVelocity; // 속도*(-1)
		vFriction = vFriction.Normalize() * m_fFriction * DT * m_fMass; // 마찰력 단위 벡터 * 원래의 마찰력 * DT -> 한 프레임에서 실제로 가해지는 마찰력 값
		
		// 마찰력이 속도보다 커서 오히려 진행방향의 반대방향으로 움직임이 이루어지는걸 방지
		if (m_vVelocity.Length() < vFriction.Length())
		{
			m_vVelocity = Vec(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction; // 기존의 속도에 마찰력을 더한다.
		}
	}

	// 속도에 맞게 물체를 이동시킨다.
	Vec vPos = GetOwnerObject()->GetPos() + m_vVelocity * DT;
	GetOwnerObject()->SetPos(vPos);

	m_vForce = Vec(0.f, 0.f);
}