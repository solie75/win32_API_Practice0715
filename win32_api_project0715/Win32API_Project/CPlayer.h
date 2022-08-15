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
    //virtual void ObjRender(HDC _dc) override; 
    // �ִϸ��̼��� ����Կ� ���� Cplayer::render ���� ����� �̹����� ���� �������� Cobject::Render() �� component render �� ȣ���ϴ� ������ ���� ������ ��ek.
    // -> �ٷ� ComponentRender �� ȣ���Ѵ�. (�θ� ������Ʈ�� CObject�� objRender �� �ڵ����� ȣ��ȴ�...?)

    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) override;

public:
    virtual CPlayer* Clone() { return new CPlayer(*this); }
public:
    CPlayer();
    ~CPlayer();
};

