#pragma once
#include "CComponent.h"
class CRigidBody :
    public CComponent
{
private: // 객체가 가지고 있는 여러 물리량 값
    Vec m_vForce; // 객체에 누적된 힘
    Vec m_vAccel; // 객체가 가지는 가속도
    Vec m_vVelocity; // 객체의 속도

    float m_fMass; // 객체의 질량
    float m_fFriction; // 마찰력


public:
    virtual void ComponentTick() override;
    //virtual void ComponentRender(HDC _dc) override;

public:
    void AddForce(Vec _vF)
    {
        m_vForce += _vF; 
    }

public:
    CRigidBody();
    ~CRigidBody();

};

