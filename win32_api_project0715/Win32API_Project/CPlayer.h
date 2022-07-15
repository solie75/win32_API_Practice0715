#pragma once
#include "CObject.h"
class CPlayer :
    public CObject
{
public:
    float m_fSpeed;
    float m_AccTime;

public:
    virtual void ObjTick() override;

public:
    CPlayer();
    ~CPlayer();
};

