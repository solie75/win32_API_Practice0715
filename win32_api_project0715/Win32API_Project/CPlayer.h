#pragma once
#include "CObject.h"
class CPlayer :
    public CObject
{
public:
    float m_fSpeed;

public:
    virtual void ObjTick() override;

public:
    CPlayer();
    ~CPlayer();
};

