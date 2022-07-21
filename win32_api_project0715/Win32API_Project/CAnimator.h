#pragma once
#include "CComponent.h"
class CAnimator :
    public CComponent
{
public:
virtual void ComponentTick() override;

public:
    CAnimator();
    ~CAnimator();
};

