#include "stdafx.h"
#include "CAnimator.h"
#include "CAnimation.h"

void CAnimator::ComponentTick()
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->AnimationTick();
	}
}

CAnimator::CAnimator()
	: CComponent(COMPONENT_TYPE::ANIMATOR)
	, m_pCurAnim(nullptr)
{
}

CAnimator::~CAnimator()
{
}
