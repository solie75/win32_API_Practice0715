#pragma once

class CEngine
{
public:
	SINGLE(CEngine);
private:
	HWND m_hMainWnd;
	HDC	m_hDC;

	//윈도우 해상도 설정
	POINT m_pResolution;

	HBITMAP m_hSecondBitmap; // 두번째 비트맵
	HDC m_hSecondDC; // 두번쩨 DC

public:
	HWND GetInstance() { return m_hMainWnd; };

	void EngineInit(HWND _hWnd, UINT _Width, UINT _Height);

	void EngineTick();
};