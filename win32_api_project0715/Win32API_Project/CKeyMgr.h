#pragma once
// enum class 를 사용하게 되면 원래 한 프로젝트 안에서  enum 끼리 같은 단어를 사용하지 못했던 것과 달리
// 같은 단어를 사용할 수 있게 된다. 하지만 그에 대한 조건으로 enum 요소를 사용할 때 enum 내용을 명시해주어야 한다.
enum class KEY_TYPE
{
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,

	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,

	Z,
	X,
	C,
	V,
	B,
	N,
	M,

	ENTER,
	ESC,
	LSHIFT,
	LALT,
	LCTRL,
	SPACE,

	LEFT,
	RIGHT,
	UP,
	DOWN,

	LBTN,
	RBTN,

	NUM_0,
	NUM_1,
	NUM_2,
	NUM_3,
	NUM_4,
	NUM_5,
	NUM_6,
	NUM_7,
	NUM_8,
	NUM_9,

	N_0,
	N_1,
	N_2,
	N_3,
	N_4,
	N_5,
	N_6,
	N_7,
	N_8,
	N_9,


	END,
};

enum KEY_STATE
{
	TAP,
	PRESS,
	RELEASE,
	NONE,
};

struct tKeyInfo
{
	KEY_TYPE kType;
	KEY_STATE kState;
	bool bPrevPress;
};

class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo> m_vecKey;

public:
	void KeyMgrInit();
	void KeyMgrTick();

public:
	KEY_STATE GetKeyState(KEY_TYPE _key)
	{
		return m_vecKey[(UINT)_key].kState;
	}
};

