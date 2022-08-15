#include "stdafx.h"
#include "CAnimator.h"
#include "CAnimation.h"

CAnimator::CAnimator()
	: CComponent(COMPONENT_TYPE::ANIMATOR)
	, m_pCurAnim(nullptr)
	, m_bRepeat(false)
{
}

CAnimator::~CAnimator()
{
	Safe_Del_Map(m_mapAnim);
}


void CAnimator::ComponentTick()
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->AnimationTick();

		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			// 반복재생하는 애니메이션이면서 현재 마지막 프레임이라면 현재 애니메이션을 리셋한다.
			m_pCurAnim->Reset();
		}
	}
}

void CAnimator::ComponentRender(HDC _dc)
{
	if (nullptr != m_pCurAnim)
	{
		if (nullptr != m_pCurAnim)
			m_pCurAnim->AnimationRender(_dc);
	}
}

CAnimation* CAnimator::FindAnimator(const wstring& _strKey)
{
	map<wstring, CAnimation*>::const_iterator iter = m_mapAnim.find(_strKey);
	
	// 찾는 애니메이션이 없는 경우
	if (iter == m_mapAnim.end())
	{
		return nullptr;
	}

	// 애니메이션을 찾은 경우
	return iter->second;
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimator(_strName); 
	m_pCurAnim->Reset(); // 애니메이션이 다시 재생될 경우 처음부터 재생하기 위해서 리셋한다.
	m_bRepeat = _bRepeat;
}

void CAnimator::CreateAnimator(const wstring& _strName, CImage* _pImage, Vec _vLeftTop
	, Vec _vSize, Vec _vOffset,float _fStep, UINT _iFrmCount
	, float _fDuration, bool _bCamRelation)
{
	CAnimation* pAnim = FindAnimator(_strName);

	if (nullptr != pAnim)
	{
		MessageBox(nullptr, L"Animation 이름 중복", L"Animation 생성 실패", MB_OK);
		return;
	}

	pAnim = new CAnimation;
	pAnim->CreateAnimation(_pImage, _vLeftTop, _vSize, _vOffset, _fStep, _iFrmCount, _fDuration, _bCamRelation);
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this; // 여기에서 m_pAnimator 의 자료형은  CAnimator* 이다. -> Animation 은 Animator 를 알게 된다.
	m_mapAnim.insert(make_pair(_strName, pAnim));
}


