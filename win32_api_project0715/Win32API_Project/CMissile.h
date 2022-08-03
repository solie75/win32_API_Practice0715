#pragma once
#include "CObject.h"

class CImage;

class CMissile :
    public CObject
{
private:
    CImage* MissileImage;
    float m_MissileSpeed;

public:
    virtual void ObjTick() override;
    virtual void ObjRender(HDC _dc) override;

public:
    CMissile* Clone() { return new CMissile(*this); }

public:
    CMissile();
    ~CMissile();
};

