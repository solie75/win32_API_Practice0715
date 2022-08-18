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

	VK_RETURN,
	VK_ESCAPE,
	VK_LSHIFT,
	VK_LMENU,
	VK_LCONTROL,
	VK_SPACE,

	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	VK_LBUTTON,
	VK_RBUTTON,

	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9,

	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
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
	// 현재 프로젝트의 윈도우가 포커스 되어 있는지에 대한 조건
	if (GetFocus())
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

		// 프로젝트 윈도우 창 내에서 마우스 좌표 알기
		POINT ptMouse = {};
		GetCursorPos(&ptMouse);
		ScreenToClient(CEngine::GetInst()->GetMainHwnd(), &ptMouse);
		m_vMousePos = ptMouse;
	}

	else
	{
		for (UINT i = 0; i < (UINT)KEY_TYPE::END; i++)
		{
		// 프레스가 되어 있는 키값에 윈도우가 포커스를 벗어났다면 바도 NONE 으로 하는 것이아니라 나머지 과정을 다 수행한 뒤에 NONE 이 되도록 해야한다.
			// 예를 들어 press 일 때에는 눌린 상태 release 상태에서는 안 눌린 상태인 버튼을 구현한 다고 할 때,
			// 눌린 상태에서 포커스가 벗어나 져 NONE이 된다면 버튼이 다시 윈도우가 포커스가 되고 누르고 있지 않은 상황임에도 눌려잇는 이미지 그대로 일 것이기 때문이다.
			m_vecKey[i].kState;
			m_vecKey[i].bPrevPress = false;
			if (KEY_STATE::TAP == m_vecKey[i].kState || KEY_STATE::PRESS == m_vecKey[i].kState)
			{
				m_vecKey[i].kState = KEY_STATE::RELEASE;
			}
			else if (KEY_STATE::RELEASE == m_vecKey[i].kState)
		{
				m_vecKey[i].kState = KEY_STATE::NONE;
			}

			m_vecKey[i].bPrevPress = false;
		}
	}
	
}
