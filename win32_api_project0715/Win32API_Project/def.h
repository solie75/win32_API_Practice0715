#pragma once

#define SINGLE(type) public:\
static type* GetInst()\
{\
	static type mgr;\
	return &mgr;\
}\
private:\
	type();\
	~type();

#define DT CTimeMgr::GetInst()->GetDeltaTime()

#define IsPressed(KEY) KEY_STATE::PRESS == CKeyMgr::GetInst()->GetKeyState(KEY)
#define IsTap(KEY) KEY_STATE::TAP == CKeyMgr::GetInst()->GetKeyState(KEY)
#define IsRelease(KEY) KEY_STATE::RELEASE == CKeyMgr::GetInst()->GetKeyState(KEY)

#define SAFE_DELETE(p) if(nullptr != p){delete p; p = nullptr;}

// Layer
#define MAX_LAYER 16

#define PI 3.14159265f

enum SCENE_TYPE
{
	LOGO,
	START,
	STAGE_01,
	END,
};

enum class PEN_COLOR
{
	RED,
	BLUE,
	GREEN,

	END,
};

enum class BRUSH_COLOR
{
	HOLLOW,
	BLACK,
	GRAY,

	END,
};

enum class COMPONENT_TYPE
{
	// Component의 순서에 따라 화면에 표현된다.
	ANIMATOR,
	COLLIDER,
	RIGIDBODY,
	GRAVITY,
	END,
};



enum class LAYER_TYPE
{
	DEFAULT,
	BACKGROUND,
	TILE,
	PLAYER,
	PLAYER_PROJECTILE,
	MONSTER,
	MONSTER_PROJECTILE,

	UI = MAX_LAYER -1,
	END = MAX_LAYER,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT, // first : object ptr, second : layer
	DELETE_OBJECT,
	SCENE_CHANGE,

	END,
};