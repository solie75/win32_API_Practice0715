#pragma once
#include "CObject.h"

class CImage;

class CPlayer :
    public CObject
{
public:
    float m_fSpeed;
    float m_AccTime;

public:
    virtual void ObjTick() override;
    virtual void ObjRender(HDC _dc) override;

public:
    virtual CPlayer* Clone() { return new CPlayer(*this); }
public:
    CPlayer();
    ~CPlayer();
};

