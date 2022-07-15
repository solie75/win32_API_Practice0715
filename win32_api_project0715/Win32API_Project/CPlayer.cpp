#include "stdafx.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"

void CPlayer::ObjTick()
{
	m_AccTime += DT;

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
	{
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
	if (IsPressed(KEY_TYPE::SPACE))
	{
		if (m_AccTime >= 0.1f)
		{
			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
			CMissile* pMissile = new CMissile;

			pMissile->SetPos(GetPos());
			pMissile->SetScale(Vec(20.f, 20.f));

			pCurScene->AddObject(pMissile);

			m_AccTime = 0.f;
		}
		
	}

	SetPos(vPos);
}

CPlayer::CPlayer()
	: m_fSpeed(200.f)
	, m_AccTime(0.f)
{
}

CPlayer::~CPlayer()
{
}
