
#include "stdafx.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"

CEngine::CEngine()
	: m_hMainWnd(0)
	, m_hDC(0)
{
}
CEngine::~CEngine() 
{
}

void CEngine::EngineInit(HWND _hWnd)
{
	m_hMainWnd = _hWnd;

	m_hDC = GetDC(m_hMainWnd);

	CSceneMgr::GetInst()->CSceneMgrInit();
	CTimeMgr::GetInst()->TimeMgrInit();
	CKeyMgr::GetInst()->KeyMgrInit();
}

void CEngine::EngineTick()
{
	CSceneMgr::GetInst()->CSceneMgrTick();
	CTimeMgr::GetInst()->TimeMgrTick();
	CKeyMgr::GetInst()->KeyMgrTick();

	CSceneMgr::GetInst()->CSceneMgrRender(m_hDC);
	CTimeMgr::GetInst()->TimeMgrRender(m_hDC);
}
