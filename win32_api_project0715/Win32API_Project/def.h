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
	COLLIDER,
	ANIMATOR,
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