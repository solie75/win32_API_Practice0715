#include "stdafx.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

void CPlayer::ObjTick()
{
	Vec vPos = GetPos();

	//if (GetAsyncKeyState('W') & 0x8000)
	if(IsPressed(KEY_TYPE::W))
	{
		vPos.y -= m_fSpeed * DT;
	}
	//if (IsRelease(KEY_TYPE::W))
	//{
	//	//vPos.y -= m_fSpeed * DT;
	//	vPos.y -= 50.f;
	//}
	if (GetAsyncKeyState('S') & 0x8000)
	{;
		vPos.y += m_fSpeed * DT;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		vPos.x -= m_fSpeed * DT;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		vPos.x += m_fSpeed * DT;
	}

	SetPos(vPos);
}

CPlayer::CPlayer()
	: m_fSpeed(200.f)
{
}

CPlayer::~CPlayer()
{
}
