#include "stdafx.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CEngine.h"
#include "CImage.h"
#include "CResMgr.h"

CPlayer::CPlayer()
	: m_fSpeed(200.f)
	, m_AccTime(0.f)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::ObjTick()
{
	m_AccTime += DT;

	Vec vPos = GetPos();

	//if (GetAsyncKeyState('W') & 0x8000)
	if(IsPressed(KEY_TYPE::UP))
	{
		vPos.y -= m_fSpeed * DT;
	}
	if (IsPressed(KEY_TYPE::DOWN))
	{
		vPos.y += m_fSpeed * DT;
	}
	if (IsPressed(KEY_TYPE::LEFT))
	{
		vPos.x -= m_fSpeed * DT;
	}
	if (IsPressed(KEY_TYPE::RIGHT))
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

			pCurScene->AddObject( pMissile);

			m_AccTime = 0.f;
		}
		
	}

	SetPos(vPos);
}

void CPlayer::ObjRender(HDC _dc) // 여기에서 들어오는 dc 는 SecondDC 이다.
{
	CImage* pImage = CResMgr::GetInst()->FindImg(L"PlayerImage");

	if (nullptr == pImage)
	{
		return;
	}

	Vec vPos = GetPos();
	//BitBlt(_dc, (int)vPos.x - 61, (int)vPos.y - 62, 123, 124, pImage->GetImageDC(), 0, 0, SRCCOPY);
	TransparentBlt(_dc, (int)vPos.x - pImage->GetWidth() / 2, (int)vPos.y - pImage->GetHeight() / 2
		, pImage->GetWidth(), pImage->GetHeight()
		, pImage->GetImageDC(), 0, 0, pImage->GetWidth(), pImage->GetHeight(), RGB(255, 0, 255));
}
