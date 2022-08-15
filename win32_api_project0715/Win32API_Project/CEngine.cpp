
#include "stdafx.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CImage.h"
#include "CEventMgr.h"

CEngine::CEngine()
	: m_hMainWnd(0)
	, m_hDC(0)
	//, m_pResolution()
	/*, m_hSecondBitmap(0)
	, m_hSecondDC(0)*/
{
}
CEngine::~CEngine() 
{
	ReleaseDC(m_hMainWnd, m_hDC);
	/*DeleteDC(m_hSecondDC);
	DeleteObject(m_hSecondBitmap);*/

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
	m_pBackBuffer = CResMgr::GetInst()->CreateImage(L"BackBuffer", m_pResolution.x, m_pResolution.y);
	

	// Mgr 초기화
	CPathMgr::GetInst()->PathMgrInit();
	CSceneMgr::GetInst()->CSceneMgrInit();
	CTimeMgr::GetInst()->TimeMgrInit();
	CKeyMgr::GetInst()->KeyMgrInit();
	CResMgr::GetInst()->ResMgrInit();

	CCameraMgr::GetInst()->CameraMgrInit();
	
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
	// 매니저 업데이트
	CTimeMgr::GetInst()->TimeMgrTick();
	CKeyMgr::GetInst()->KeyMgrTick();
	CCameraMgr::GetInst()->CameraMgrTick();
	
	// Scene 업데이트
	CSceneMgr::GetInst()->CSceneMgrTick();

	// 충돌 검사
	CCollisionMgr::GetInst()->CollisionMgrTick();
	// 함수 자체는 collider 에게 줬지만 그 collider 가 본인을 소유하고 있는 object 쪽으로 다시 가상함수를 재호출
	// 시켜서 각 object 클라스 쪽에 override 시켜 놓은 beginoverlap, overlap, endoverlap 이 상황에 맞게 들어 온다.



	// 렌더링
	// clear 부분
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(m_pBackBuffer->GetImageDC(), m_arrBrush[(UINT)BRUSH_COLOR::GRAY]);
	Rectangle(m_pBackBuffer->GetImageDC(), -1, -1, m_pResolution.x + 1, m_pResolution.y + 1); // 이렇게 되면 세컨드 비트맵 화면 전체가 clear 된다.
	// 굳이 기본이 흰색인 세컨드 비트맵 생성에 회색을 넣어주고 그에 대한 반환값의 기본의 흰색을 다시 세컨드 비트맵에 넣는이유는..?
	SelectObject(m_pBackBuffer->GetImageDC(), hPrevBrush);

	/*CSceneMgr::GetInst()->CSceneMgrRender(m_hDC);
	CTimeMgr::GetInst()->TimeMgrRender(m_hDC);*/
	CSceneMgr::GetInst()->CSceneMgrRender(m_pBackBuffer->GetImageDC());
	CTimeMgr::GetInst()->TimeMgrRender(m_pBackBuffer->GetImageDC());
	CCameraMgr::GetInst()->CameraMgrRender(m_pBackBuffer->GetImageDC());


	BitBlt(m_hDC, 0, 0, m_pResolution.x, m_pResolution.y, m_pBackBuffer->GetImageDC(), 0, 0, SRCCOPY);

	// EventMgr
	// 해당 프레임의 이벤트를 쌓아 놓고 다음 프레임에 넘긴다.
	CEventMgr::GetInst()->EventMgrTick();

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
