#pragma once
#include "CObject.h"

class CImage;

class CMissile :
    public CObject
{
private:
    CImage* m_MissileImage;
    float m_MissileSpeed;

    float m_fDir; // 이동방향 (라디안)
    Vec m_vDir; // 벡터
    // 속력까지 포함하고 있는 벡터 보다는 순수한 속력은  float값으로 따로 관리하고
    // 방향성은 벡터로 표현한다.

public:
    void SetDir(float _fDir) { m_fDir = _fDir; }
    void SetDir(Vec _vDir)
    { 
        m_vDir = _vDir;
        m_vDir.Normalize();
    }

    Vec GetDir() { return m_vDir; }

    virtual void ObjTick() override;
    virtual void ObjRender(HDC _dc) override;

public:
    CMissile* Clone() { return new CMissile(*this); }

public:
    CMissile();
    ~CMissile();
};

