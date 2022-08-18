#pragma once
#include "CObject.h"
class CForce :
    public CObject
{
private:
    float m_fForce; // ���� ũ��
    float m_fRadius; // ���� �ݰ�
    float m_fDuration; // �� ���� �ð�

    float m_fAccTime; // ���� �ð�

public:
    void SetForceInfo(float _fForce, float _fRadian, float _fDuration)
    {
        m_fForce = _fForce;
        m_fRadius = _fRadian;
        m_fDuration = _fDuration;
    }

public:
    virtual void ObjTick() override;
    virtual void ObjRender(HDC _dc) override;

    CForce* Clone() { return new CForce(*this); }

public:
    CForce();
    virtual ~CForce();
};

