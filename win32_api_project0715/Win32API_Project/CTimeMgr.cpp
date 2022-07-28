#include "stdafx.h"
#include "cTimeMgr.h"
#include "CEngine.h"

CTimeMgr::CTimeMgr()
	: m_Frequence{}
	, m_CurCount{}
	, m_PrevCount{}
	, m_DeltaTime(0.f)
	, m_AccTime(0.f)
{
}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::TimeMgrInit()
{
	// 성능 카운터의 빈도를 검색. lpFreaquency = 현재 성능 카운터, 타이머의 주파수를 반환한다.
	QueryPerformanceFrequency(&m_Frequence);
	// 시간 간격 측정에 사용할 수 있는 고해상도 타임 스탬프인 성능 카운터의 현재 값을 검색한다. (현재 CPU 의 틱을 받아오는 것)
	// lpPerformanceCounter = 매개변수로 현재 성능 카운터 값을 게수로 받는 변수에 대한 포인터를 넘겨준다.
	QueryPerformanceCounter(&m_PrevCount);
}

void CTimeMgr::TimeMgrTick()
{
	QueryPerformanceCounter(&m_CurCount);

	m_DeltaTime = (float)(m_CurCount.QuadPart - m_PrevCount.QuadPart) / (float)(m_Frequence.QuadPart);

	m_PrevCount.QuadPart = m_CurCount.QuadPart;
}

void CTimeMgr::TimeMgrRender(HDC _dc)
{
	

	//TextOut(_dc, 10, 10, szFloat, iLen);  // 계속 화면에 출력되기 때문에 원래 출력하려 했던 객체에 방해가 될 수 있다.
	// ->
	//SetWindowText(hWnd, szFloat); // 윈도우 창의 이름 부분에 FPS를 출력하는 방법 // 대신에 실시간 대신에 1초에 한번 뜨게 끔 하자

	// 1초를 구하는 코드 : Deleta Time 이 프레임 한번도는 시간이니 이 것을 축적해서 1초가 넘어가면 fps 출력
	//1. TimeMgr 에 축적되는 시간을 뜻하는 AccTime 변수 생성

	m_AccTime += m_DeltaTime;

	if ((1.f) < m_AccTime)
	{
		HWND hWnd = CEngine::GetInst()->GetInstance(); // SetWindowText()에 인자로 주기 위한 메인 함수 핸들

		wchar_t szFloat[50] = {};

		float FPS = 1.f / m_DeltaTime;

		swprintf_s(szFloat, 50, L"DeltaTime : %f", FPS);
		int iLen = (int)wcsnlen_s(szFloat, 50);

		SetWindowTextW(hWnd, szFloat);
		m_AccTime = 0.f;
	}

}
