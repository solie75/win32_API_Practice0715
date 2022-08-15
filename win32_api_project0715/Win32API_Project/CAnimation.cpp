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
	if (m_bFinish == true) // 애니메이션 프레임이 마지막에 해당하는 경우
	{
		return;
	}

	m_fAccTime += DT;

	// 누적 시간이 정해진 한 애니메이션 프레임 지속 시간을 초과하면 다음 애니메이션으로 넘어간다.
	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		
		// m_fAccTime = 0.f; // 다음 애니메이션 프레임으로 넘어갈 때 누적시간을 0으로 초기화 시키는 것이 아니라
		// 누적시간에서 애니메이션 프레임 지속시간을 빼준다면
		// 다음 애니메이션 프레임 때에 전 애니메이션 프레임 실행당시 초과한 시간 만큼 해당 애니메이션 프레임은 시간을 덜사용하게 된다.
		// 이 계산으로 인해 결국 원래 의도 했던 각 애니메이션프레임 시간에 최대한 가깝게 아니메이션 프레임 전환이 이루어진다.
		m_fAccTime -= m_vecFrm[m_iCurFrm].fDuration;

		// 벡터의 인덱스를 초과한 경우, 즉 Animation 이 1회 재싱이 완료된 경우
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

	// Frame 의 Offset 을 더한다. ==> 최종 위치
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

