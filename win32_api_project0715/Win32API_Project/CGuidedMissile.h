#pragma once
#include "CMissile.h"

class CGuidedMissile :
    public CMissile
{
private:
    CObject* m_pTarget; // 타겟정보
    float m_fRotateSpeed; // 회전속도

    float m_fDetectRange; // 탐지범위

private:
    void FindTarget();


public:
    virtual void ObjTick() override;
    virtual void ObjRender(HDC _dc) override;

public:
    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) override;

public:
    CGuidedMissile();
    ~CGuidedMissile();
};

