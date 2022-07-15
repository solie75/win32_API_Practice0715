
#include "stdafx.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"

CEngine::CEngine()
	: m_hMainWnd(0)
	, m_hDC(0)
	, m_pResolution()
{
}
CEngine::~CEngine() 
{
}

void CEngine::EngineInit(HWND _hWnd, UINT _Width, UINT _Height)
{
	m_hMainWnd = _hWnd;

	m_hDC = GetDC(m_hMainWnd);

	//윈도우 해상도 설정
	m_pResolution.x = _Width;
	m_pResolution.y = _Height;

	// 그냥 SetwindowPos 를 호출하면 내가 원하는 작업 영역이 아닌 전체 창 크기로 지정되어 버린다.
	// 그래서 SetWindowPos 전에 AdjustWindowRect()를 사용해서 내가 원하는 작업영역을 가져오는 전체 창 크기를 계산해 준다. 그것을 SetWindow에 입력
	RECT rt = {0, 0, _Width, _Height};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false); // 원하는 작업영역 크기, 윈도우 스타일, 메뉴바 유무
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right -rt.left, rt.bottom - rt.top, 0);
	ShowWindow(m_hMainWnd, true);

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
