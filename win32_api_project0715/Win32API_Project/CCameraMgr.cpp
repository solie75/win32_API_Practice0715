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

	// ó���� ī�޶� ȿ���� �ִٸ�
	if (!m_CameraEffectInfoList.empty())
	{
		CameraEffectInfo& info = m_CameraEffectInfoList.front(); // ī�޶� ȿ�� ����Ʈ�� �� �� ��带 �����Ѵ�.

		info.m_fAccTime += DT; // ���� ���ǿ��� DT�� �ŵ� ����  m_fAccTime �� �̼��ϰ�  m_fDuration �� ���� �� �ִ�.
		float fRatio = (info. m_fAccTime / info.m_fDuration); // ���� �ð� ��� ���� �ð��� ������ 0~ 1 ���̷� ȯ��

		if (1.f < fRatio)
		{
			fRatio = 1.f; //  m_fAccTime �� m_fDuration �� ��¦ �ʰ� �ϴ� ��츦 ����Ͽ� �ִ� ���� �ð� ��� ���� �ð��� ������ 1�� �����Ѵ�.
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
