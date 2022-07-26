#pragma once
#include "CObject.h"
#include "CImage.h"

class CMonster :
	public CObject
{
private:
	CImage* m_MonsterImage;

public:
	virtual void ObjTick() override;
	virtual void ObjRender(HDC _dc) override;

public:
	CMonster* Clone() { return new CMonster(*this); }

public:
	CMonster();
	~CMonster();
};

