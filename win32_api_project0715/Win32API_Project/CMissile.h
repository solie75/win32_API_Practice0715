#pragma once
#include "CObject.h"
class CMissile :
    public CObject
{
private:
    float m_MissileSpeed;

public:
    virtual void ObjTick() override;
    virtual void ObjRender(HDC _dc) override;

public:
    virtual CMissile* Clone() { return new CMissile(*this); }

public:
    CMissile();
    ~CMissile();
};

