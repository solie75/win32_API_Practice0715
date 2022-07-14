#include "stdafx.h"
#include "CSceneMgr.h"
#include "CScene_Logo.h"

void CSceneMgr::CSceneMgrInit()
{
	m_arrScene[LOGO] = new CScene_Logo;
	m_arrScene[LOGO]->SceneInit();

	m_pCurScene = m_arrScene[LOGO];
}

void CSceneMgr::CSceneMgrTick()
{
	m_pCurScene->SceneTick();
}

void CSceneMgr::CSceneMgrRender(HDC _dc)
{
	m_pCurScene->SceneRender(_dc);
}

CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{

}

CSceneMgr::~CSceneMgr()
{
	for (int i = 0; i < SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}