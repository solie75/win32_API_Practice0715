#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr)
private:
	LARGE_INTEGER	m_Frequence;
	LARGE_INTEGER	m_CurCount;
	LARGE_INTEGER	m_PrevCount;

	float			m_AccTime;
	float			m_DeltaTime;

public:
	void TimeMgrInit();
	void TimeMgrTick();
	void TimeMgrRender(HDC _dc);

public:
	float GetDeltaTime()
	{
		return m_DeltaTime;
	}
};

