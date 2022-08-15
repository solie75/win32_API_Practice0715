#include "stdafx.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CObject.h"
#include "CCameraMgr.h"
#include "CTimeMgr.h"
#include "CImage.h"


CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pImage(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bCamRelation(false)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::AnimationTick()
{
	if (m_bFinish == true) // �ִϸ��̼� �������� �������� �ش��ϴ� ���
	{
		return;
	}

	m_fAccTime += DT;

	// ���� �ð��� ������ �� �ִϸ��̼� ������ ���� �ð��� �ʰ��ϸ� ���� �ִϸ��̼����� �Ѿ��.
	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		
		// m_fAccTime = 0.f; // ���� �ִϸ��̼� ���������� �Ѿ �� �����ð��� 0���� �ʱ�ȭ ��Ű�� ���� �ƴ϶�
		// �����ð����� �ִϸ��̼� ������ ���ӽð��� ���شٸ�
		// ���� �ִϸ��̼� ������ ���� �� �ִϸ��̼� ������ ������ �ʰ��� �ð� ��ŭ �ش� �ִϸ��̼� �������� �ð��� ������ϰ� �ȴ�.
		// �� ������� ���� �ᱹ ���� �ǵ� �ߴ� �� �ִϸ��̼������� �ð��� �ִ��� ������ �ƴϸ��̼� ������ ��ȯ�� �̷������.
		m_fAccTime -= m_vecFrm[m_iCurFrm].fDuration;

		// ������ �ε����� �ʰ��� ���, �� Animation �� 1ȸ ����� �Ϸ�� ���
		if (m_vecFrm.size() <= m_iCurFrm +1)
		{
			m_bFinish = true;
		}
		else
		{
			++m_iCurFrm;
		}
	}
}

void CAnimation::AnimationRender(HDC _dc)
{
	CObject* pOwner = m_pAnimator->GetOwnerObject();
	Vec vPos = pOwner->GetPos();

	if (m_bCamRelation)
	{
		vPos = CCameraMgr::GetInst()->GetRenderPos(vPos);
	}

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	// Frame �� Offset �� ���Ѵ�. ==> ���� ��ġ
	vPos += m_vecFrm[m_iCurFrm].vOffSet;

	AlphaBlend(_dc
		, int(vPos.x - m_vecFrm[m_iCurFrm].vSize.x / 2.f)
		, int(vPos.y - m_vecFrm[m_iCurFrm].vSize.y / 2.f)
		, int(m_vecFrm[m_iCurFrm].vSize.x)
		, int(m_vecFrm[m_iCurFrm].vSize.y)
		, m_pImage->GetImageDC()
		, int(m_vecFrm[m_iCurFrm].vLeftTop.x), int(m_vecFrm[m_iCurFrm].vLeftTop.y)
		, int(m_vecFrm[m_iCurFrm].vSize.x), int(m_vecFrm[m_iCurFrm].vSize.y)
		, tFunc);
} 

void CAnimation::CreateAnimation(CImage* _pImage, Vec _vLeftTop, Vec _vSize, Vec _vOffset
	, float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation)
{
	m_pImage = _pImage;

	m_bCamRelation = _bCamRelation;

	for (UINT i = 0; i < _iFrmCount; ++i)
	{
		tAnimFrm frm = {};

		frm.vLeftTop.x = _vLeftTop.x + (_fStep * (float)i);
		frm.vLeftTop.y = _vLeftTop.y; // ...?
		frm.vSize = _vSize;
		frm.vOffSet = _vOffset;
		frm.fDuration = _fDuration;

		m_vecFrm.push_back(frm);
	}
}

