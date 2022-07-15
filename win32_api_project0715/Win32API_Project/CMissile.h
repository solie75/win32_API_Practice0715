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
    CMissile();
    ~CMissile();
};

