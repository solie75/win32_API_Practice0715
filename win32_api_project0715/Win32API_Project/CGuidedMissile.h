#pragma once
#include "CMissile.h"

class CGuidedMissile :
    public CMissile
{
private:
    CObject* m_pTarget; // Ÿ������
    float m_fRotateSpeed; // ȸ���ӵ�

    float m_fDetectRange; // Ž������

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

