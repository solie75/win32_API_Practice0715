#include "stdafx.h"
#include "CKeyMgr.h"

int vkarr[(UINT)KEY_TYPE::END]
=
{
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',
};

CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::KeyMgrInit()
{
	for (UINT i = 0; i < (UINT)KEY_TYPE::END; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ (KEY_TYPE)i, KEY_STATE::NONE, false });
	}
}

void CKeyMgr::KeyMgrTick()
{
	for (UINT i = 0; i < (UINT)KEY_TYPE::END; ++i)
	{
		// 해당 키가 현재 눌려있다.
		if (GetAsyncKeyState(vkarr[i]) & 0x8000)// 여기 GetAsyncKeyState 에 인자로 문자를 주어야 하기 때문에 위에 vkarr 을 만들어서 enum KEY_TYPE의 요소들을 문자로 바꿔주는 일을 하게 할것
		{
			// 이전 프레임에도 눌려있다.
			if (m_vecKey[i].bPrevPress)
			{
				m_vecKey[i].kState = KEY_STATE::PRESS;
			}
			else
			{
				m_vecKey[i].kState = KEY_STATE::TAP;
			}
			m_vecKey[i].bPrevPress = true;
		}
		// 해당 키가 현재 눌려 있지 않다.
		else
		{
			// 이전 프레임에는 눌렸었다.
			if (m_vecKey[i].bPrevPress)
			{
				m_vecKey[i].kState = KEY_STATE::RELEASE;
			}
			// 이전 프레임에도 눌려있지 않았다.
			else
			{
				m_vecKey[i].kState = KEY_STATE::NONE;
			}
			m_vecKey[i].bPrevPress = false;
		}
	}
}
