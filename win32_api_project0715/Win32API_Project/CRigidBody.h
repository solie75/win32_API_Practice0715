#pragma once
#include "CComponent.h"
class CRigidBody :
    public CComponent
{
private: // ��ü�� ������ �ִ� ���� ������ ��
    Vec m_vForce; // ��ü�� ������ ��
    Vec m_vAccel; // ��ü�� ������ ���ӵ�
    Vec m_vVelocity; // ��ü�� �ӵ�

    float m_fMass; // ��ü�� ����
    float m_fFriction; // ������


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

