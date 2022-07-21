#pragma once
#include "CComponent.h"

class CCollider :
	public CComponent
{
public:
	virtual void ComponentTick() override;
	virtual void ComponentRender(HDC _dc) override;
public:
	CCollider();
	~CCollider();
};

