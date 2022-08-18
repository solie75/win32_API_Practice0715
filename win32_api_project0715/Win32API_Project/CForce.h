#pragma once
#include "CObject.h"
class CForce :
    public CObject
{
private:
    float m_fForce; // 힘의 크기
    float m_fRadius; // 힘의 반경
    float m_fDuration; // 힘 유지 시간

    float m_fAccTime; // 누적 시간

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

