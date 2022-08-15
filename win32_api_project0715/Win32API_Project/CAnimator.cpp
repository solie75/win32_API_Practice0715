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
			// �ݺ�����ϴ� �ִϸ��̼��̸鼭 ���� ������ �������̶�� ���� �ִϸ��̼��� �����Ѵ�.
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
	
	// ã�� �ִϸ��̼��� ���� ���
	if (iter == m_mapAnim.end())
	{
		return nullptr;
	}

	// �ִϸ��̼��� ã�� ���
	return iter->second;
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimator(_strName); 
	m_pCurAnim->Reset(); // �ִϸ��̼��� �ٽ� ����� ��� ó������ ����ϱ� ���ؼ� �����Ѵ�.
	m_bRepeat = _bRepeat;
}

void CAnimator::CreateAnimator(const wstring& _strName, CImage* _pImage, Vec _vLeftTop
	, Vec _vSize, Vec _vOffset,float _fStep, UINT _iFrmCount
	, float _fDuration, bool _bCamRelation)
{
	CAnimation* pAnim = FindAnimator(_strName);

	if (nullptr != pAnim)
	{
		MessageBox(nullptr, L"Animation �̸� �ߺ�", L"Animation ���� ����", MB_OK);
		return;
	}

	pAnim = new CAnimation;
	pAnim->CreateAnimation(_pImage, _vLeftTop, _vSize, _vOffset, _fStep, _iFrmCount, _fDuration, _bCamRelation);
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this; // ���⿡�� m_pAnimator �� �ڷ�����  CAnimator* �̴�. -> Animation �� Animator �� �˰� �ȴ�.
	m_mapAnim.insert(make_pair(_strName, pAnim));
}


