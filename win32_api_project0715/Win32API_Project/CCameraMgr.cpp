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

	// 처리할 카메라 효과가 있다면
	if (!m_CameraEffectInfoList.empty())
	{
		CameraEffectInfo& info = m_CameraEffectInfoList.front(); // 카메라 효과 리스트의 맨 앞 노드를 참조한다.

		info.m_fAccTime += DT; // 현재 조건에서 DT의 거듭 합인  m_fAccTime 이 미세하게  m_fDuration 을 넘을 수 있다.
		float fRatio = (info. m_fAccTime / info.m_fDuration); // 제한 시간 대비 진행 시간의 비율을 0~ 1 사이로 환산

		if (1.f < fRatio)
		{
			fRatio = 1.f; //  m_fAccTime 이 m_fDuration 을 살짝 초과 하는 경우를 대비하여 최대 제한 시간 대비 진행 시간의 비율을 1로 고정한다.
			m_CameraEffectInfoList.pop_front();
		}
		else
		{
			if (CAM_EFFECT::FADE_IN == info.m_eEffect)
			{
				m_fAlpha = 1.f - fRatio;
			}
			else if (CAM_EFFECT::FADE_OUT == info.m_eEffect)
			{
				m_fAlpha = fRatio;
			}
			else
			{
				m_fAlpha = 0.f;
			}
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
