#include "stdafx.h"
#include "CEntity.h"

UINT CEntity::g_GlobalID = 0; // 정적 변수 초기화

CEntity::CEntity()
	: m_ID(g_GlobalID)
{
}

CEntity::CEntity(const CEntity& _other)
	: m_strName(_other.m_strName)
	, m_ID(g_GlobalID++) // 새로 아이디를 생성할때 겹치지 않기 위해
{
}

CEntity::~CEntity()
{
}
