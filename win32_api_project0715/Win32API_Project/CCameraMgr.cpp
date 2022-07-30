#include "stdafx.h"
#include "CCameraMgr.h"
#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CImage.h"
#include "CObject.h"


CCameraMgr::CCameraMgr()
	: m_pTargetObj(nullptr)
	, m_pVeil(nullptr)
	, m_fAlpha(1.f)
	, m_fAccTime(0.f)
	, m_fMaxTime(5.f)
	, m_eEffect(CAM_EFFECT::FADE_IN)
{
	POINT ptResol = CEngine::GetInst()->GetResolution();
	m_pVeil = CResMgr::GetInst()->CreateImage(L"Veil", ptResol.x, ptResol.y);
}

CCameraMgr::~CCameraMgr()
{

}

void CCameraMgr::CameraMgrInit()
{
	m_vResolution = CEngine::GetInst()->GetResolution();
	m_vLook = (m_vResolution / 2.f);
}

void CCameraMgr::CameraMgrTick()
{
	if (IsPressed(KEY_TYPE::W))
	{
		m_vLook.y -= DT * 500.f;
	}
	if (IsPressed(KEY_TYPE::S))
	{
		m_vLook.y += DT * 500.f;
	}
	if (IsPressed(KEY_TYPE::A))
	{
		m_vLook.x -= DT * 500.f;
	}
	if (IsPressed(KEY_TYPE::D))
	{
		m_vLook.x += DT * 500.f;
	}

	if (m_pTargetObj)
	{
		m_vLook = m_pTargetObj->GetPos();
	}

	if (m_fAccTime <= 5.f)
	{
		m_fAccTime += DT;
		float fRatio =  m_fAccTime / m_fMaxTime; // 제한 시간 대비 진행 시간의 비율을 0~ 1 사이로 환산

		if (CAM_EFFECT::FADE_IN == m_eEffect)
		{
			m_fAlpha = 1.f - fRatio;
		}
		else
		{
			m_fAlpha = fRatio;
		}
	}

	m_vDiff = m_vLook - (m_vResolution / 2.f);
}

void CCameraMgr::CameraMgrRender(HDC _dc)
{
	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = 0;
	tFunc.SourceConstantAlpha = (BYTE)(255.f * m_fAlpha);

	AlphaBlend(_dc, 0, 0
		, m_pVeil->GetWidth(), m_pVeil->GetHeight()
		, m_pVeil->GetImageDC()
		, 0, 0
		, m_pVeil->GetWidth(), m_pVeil->GetHeight()
		, tFunc);
}
