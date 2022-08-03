#pragma once
#include "CComponent.h"

class CAnimation;

class CAnimator :
    public CComponent
{
private:
    map<wstring,CAnimation*> m_mapAnim;
    CAnimation* m_pCurAnim;
public:

    virtual void ComponentTick() override;

public:
    void CreateAnimation();

public:
    CAnimator();
    ~CAnimator();
};

