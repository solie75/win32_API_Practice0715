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
    // 애니메이션을 사용함에 따라 Cplayer::render 에서 비행기 이미지를 띠우고 마지막에 Cobject::Render() 로 component render 를 호출하는 구조를 취할 이유가 없ek.
    // -> 바로 ComponentRender 를 호출한다. (부모 컴포넌트인 CObject의 objRender 가 자동으로 호출된다...?)

    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) override;

public:
    virtual CPlayer* Clone() { return new CPlayer(*this); }
public:
    CPlayer();
    ~CPlayer();
};

