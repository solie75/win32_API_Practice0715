#pragma once

class CEngine
{
public:
	SINGLE(CEngine);
private:
	HWND m_hMainWnd;
	HDC	m_hDC;

public:
	HWND GetInstance() { return m_hMainWnd; };

	void EngineInit(HWND _hWnd);

	void EngineTick();
};