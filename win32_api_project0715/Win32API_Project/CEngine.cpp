
#include "stdafx.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CCollisionMgr.h"

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
	ReleaseDC(m_hMainWnd, m_hDC);
	DeleteDC(m_hSecondDC);
	DeleteObject(m_hSecondBitmap);

	// 펜 삭제
	for (UINT i = 0; i < (UINT)PEN_COLOR::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
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
	RECT rt = {0, 0, (LONG)_Width, (LONG)_Height};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false); // 원하는 작업영역 크기, 윈도우 스타일, 메뉴바 유무
	
	// 윈도우 크기 변경 및 show 설정
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right -rt.left, rt.bottom - rt.top, 0);
	ShowWindow(m_hMainWnd, true);

	CreateDefaultGDIObject();

	// 이중 버퍼링
	// 윈도우 해상도와 동일한 크기의 비트맵을 생성
	// 새로 생선한 비트맵을 가리키는 전용 DC 생성
	// 새로 생성한 비트맵과 DC를 서로 연결

	m_hSecondBitmap = CreateCompatibleBitmap(m_hDC, m_pResolution.x, m_pResolution.y);
	m_hSecondDC =  CreateCompatibleDC(m_hDC);
	// DC 를 생성하면 임의로 1픽셀의 비트맵을 가리키고 있기에 SelectObject 의 반환값을 삭제해 주어야 한다.
	HBITMAP hDefaultBitmap = (HBITMAP)SelectObject(m_hSecondDC, m_hSecondBitmap);
	DeleteObject(hDefaultBitmap);

	// Mgr 초기화
	CPathMgr::GetInst()->PathMgrInit();
	CSceneMgr::GetInst()->CSceneMgrInit();
	CTimeMgr::GetInst()->TimeMgrInit();
	CKeyMgr::GetInst()->KeyMgrInit();
	CResMgr::GetInst()->ResMgrInit();
}

void CEngine::EngineTick()
{
	// 순서
	// //업데이트
	// 1. 한번의 프레임 당 EngineTick() 호출
	// 2. Delta time의 정의와 key 의 상태에 대한 파악
	// 3. 현재 씬(CurScene)의 SceneTick()을 호출 -> 모든 ObjectTick() 호출 -> 각 객체의 모든 ComponentTick() 호출
	// 4. 현재 씬의 모든 충돌 상태를 조사
	// // 렌더링
	// 5. 세컨드 비트맵 생성 및 그에 대한 작업 영역에 맞는 사각형 생성으로 clear
	// 6. CSceneMgrRender() => CSceneRender() => ObjRender() => ComponentRender()
	// 7. BitBlt() 함수로 세컨드 비트맵을 메인 비트맵에 복사


	// 업데이트
	CTimeMgr::GetInst()->TimeMgrTick();
	CKeyMgr::GetInst()->KeyMgrTick();
	CSceneMgr::GetInst()->CSceneMgrTick();
	CCollisionMgr::GetInst()->CollisionMgrTick();


	// 렌더링
	// clear 부분
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(m_hSecondDC, m_arrBrush[(UINT)BRUSH_COLOR::GRAY]);
	Rectangle(m_hSecondDC, -1, -1, m_pResolution.x + 1, m_pResolution.y + 1); // 이렇게 되면 세컨드 비트맵 화면 전체가 clear 된다.
	// 굳이 기본이 흰색인 세컨드 비트맵 생성에 회색을 넣어주고 그에 대한 반환값의 기본의 흰색을 다시 세컨드 비트맵에 넣는이유는..?
	SelectObject(m_hSecondDC, hPrevBrush);

	/*CSceneMgr::GetInst()->CSceneMgrRender(m_hDC);
	CTimeMgr::GetInst()->TimeMgrRender(m_hDC);*/
	CSceneMgr::GetInst()->CSceneMgrRender(m_hSecondDC);
	CTimeMgr::GetInst()->TimeMgrRender(m_hSecondDC);

	BitBlt(m_hDC, 0, 0, m_pResolution.x, m_pResolution.y, m_hSecondDC, 0, 0, SRCCOPY);

}

void CEngine::CreateDefaultGDIObject()
{
	// 자주 사용할 펜 생성
	m_arrPen[(UINT)PEN_COLOR::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_COLOR::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_COLOR::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

	// 자주 사용할 브러쉬 생성
	m_arrBrush[(UINT)BRUSH_COLOR::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_COLOR::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_arrBrush[(UINT)BRUSH_COLOR::GRAY] = (HBRUSH)GetStockObject(GRAY_BRUSH);
}
