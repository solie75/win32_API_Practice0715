#pragma once
#include "CObject.h"
#include "CImage.h"
#include "CPlayer.h"

class CMonster :
	public CObject
{
private:
	CImage* m_MonsterImage;
	CPlayer* m_pPlayer;

public:
	virtual void ObjTick() override;
	virtual void ObjRender(HDC _dc) override;

public:
	virtual void CollisionBeginOverlap(CCollider* _pOhterCollider) override;

	CMonster* Clone() { return new CMonster(*this); }

public:
	CMonster();
	~CMonster();
};

