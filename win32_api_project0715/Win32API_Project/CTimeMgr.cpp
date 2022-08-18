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
	// 성능 카운터의 빈도를 검색. lpFreaquency = 현재 성능 카운터, 타이머의 주파수(1초에 각 타이머의 성능에 맞는 진동수)를 반환한다.
	QueryPerformanceFrequency(&m_Frequence);
	// 시간 간격 측정에 사용할 수 있는 고해상도 타임 스탬프인 성능 카운터의 현재 값을 검색한다. (현재 CPU 의 틱을 받아오는 것)
	// lpPerformanceCounter = 매개변수로 현재 성능 카운터 값을 게수로 받는 변수에 대한 포인터를 넘겨준다.
	QueryPerformanceCounter(&m_PrevCount);
}

void CTimeMgr::TimeMgrTick()
{
	// 여기에서 m_CurCount 는 LARGE_INTEGER 타입이다.
	// LARGE_INTEGER 타입은 LowPart(하위 32 비트 DWORD 형)과 HighPart(상위 32 비트 Long)형으로 구성되며
	// 실제 데이타 값은  QURDPART (64비트의 signed interg형)으로 되어있다.
	QueryPerformanceCounter(&m_CurCount);

	// 현재까지의 누적된 카운터에 지난 프레임의 누적 카운터를 빼서 한 프레임 사이의 카운터를 구한다.
	// 그 한 프레임의 카운터 를 
	m_DeltaTime = (float)(m_CurCount.QuadPart - m_PrevCount.QuadPart) / (float)(m_Frequence.QuadPart);
	// deltaTime 은 ' 각 컴퓨터의 성능에 따라 FPS 가 다름으로써 생기는 값의 차이를 없애기 위한 값' 이다.

	m_PrevCount.QuadPart = m_CurCount.QuadPart;

	// 60프레임을 초과한 경우 강제 60프레임 고정
	if ((1.f / 60.f) > m_DeltaTime)
	{
		m_DeltaTime = (1.f / 60.f);
	}
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
