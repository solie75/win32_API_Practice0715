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

