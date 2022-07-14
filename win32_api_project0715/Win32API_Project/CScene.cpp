#include "stdafx.h"
#include "CScene.h"
#include "CObject.h"

void CScene::SceneTick()
{
	for (size_t i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->ObjTick();
	}
}

void CScene::SceneRender(HDC _dc)
{
	for (size_t i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->ObjRender(_dc);
	}
}

CScene::CScene()
{
}

CScene::~CScene()
{
	for (size_t i = 0; i < m_vecObject.size(); ++i)
	{
		delete m_vecObject[i];
	}
}
