
#include "stdafx.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"

CEngine::CEngine()
	: m_hMainWnd(0)
	, m_hDC(0)
	, m_pResolution()
	, m_hSecondBitmap(0)
	, m_hSecondDC(0)
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

	// 비트맵 해상도를 설정하기 위한 실제 윈도우 크기 계산
	// 그냥 SetwindowPos 를 호출하면 내가 원하는 작업 영역이 아닌 전체 창 크기로 지정되어 버린다.
	// 그래서 SetWindowPos 전에 AdjustWindowRect()를 사용해서 내가 원하는 작업영역을 가져오는 전체 창 크기를 계산해 준다. 그것을 SetWindow에 입력
	RECT rt = {0, 0, _Width, _Height};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false); // 원하는 작업영역 크기, 윈도우 스타일, 메뉴바 유무
	
	// 윈도우 크기 변경 및 show 설정
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right -rt.left, rt.bottom - rt.top, 0);
	ShowWindow(m_hMainWnd, true);

	// 이중 버퍼링
	// 윈도우 해상도와 동일한 크기의 비트맵을 생성
	// 새로 생선한 비트맵을 가리키는 전용 DC 생성
	// 새로 생성한 비트맵과 DC를 서로 연결

	m_hSecondBitmap = CreateCompatibleBitmap(m_hDC, m_pResolution.x, m_pResolution.y);
	m_hSecondDC =  CreateCompatibleDC(m_hDC);
	// DC 를 생성하면 임의로 1픽셀의 비트맵을 가리키고 있기에 SelectObject 의 반환값을 삭제해 주어야 한다.
	HBITMAP hDefaultBitmap = (HBITMAP)SelectObject(m_hSecondDC, m_hSecondBitmap);
	DeleteObject(hDefaultBitmap);

	CSceneMgr::GetInst()->CSceneMgrInit();
	CTimeMgr::GetInst()->TimeMgrInit();
	CKeyMgr::GetInst()->KeyMgrInit();
}

void CEngine::EngineTick()
{
	// 업데이트
	CSceneMgr::GetInst()->CSceneMgrTick();
	CTimeMgr::GetInst()->TimeMgrTick();
	CKeyMgr::GetInst()->KeyMgrTick();


	// 렌더링
	// clear 부분
	Rectangle(m_hSecondDC, -1, -1, m_pResolution.x + 1, m_pResolution.y); // 이렇게 되면 세컨드 비트맵 화면 전체가 clear 된다.

	/*CSceneMgr::GetInst()->CSceneMgrRender(m_hDC);
	CTimeMgr::GetInst()->TimeMgrRender(m_hDC);*/
	CSceneMgr::GetInst()->CSceneMgrRender(m_hSecondDC);
	CTimeMgr::GetInst()->TimeMgrRender(m_hSecondDC);

	BitBlt(m_hDC, 0, 0, m_pResolution.x, m_pResolution.y, m_hSecondDC, 0, 0, SRCCOPY);

}
