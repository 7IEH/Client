#pragma once

#define fDT CTimeMgr::GetInst()->GETfDT()
#define DT CTimeMgr::GetInst()->GetDT()
#define RENDERPOS(POS) CCamera::GetInst()->GetRenderPos(POS)
#define KEY_CHECK(key,state) CKeyMgr::GetInst()->GetKeyState(KEY::key) == KEY_STATE::state
#define MOUSE_POS  CKeyMgr::GetInst()->GetMousePos()

#define CLONE(type)	type* clone() {return new type(*this);}

#define ADD(a,b) (a+b)
#define SINGLE(type) static type* GetInst() \
										 { \
										static type mgr; \
										return &mgr; \
										}\
									private:\
										type();\
										~type();	

#define PI 3.141592

#define TILE_SIZE	64

enum class GROUP_TYPE
{
	DEFAULT,
	TILE,
	MISSILE,
	PLAYER,
	MONSTER,
	PROJ_PLAYER,
	PROJ_MONSTER,

	UI=31,
	END=32,
};


enum class SCENE_TYPE
{
	TITLE,
	TOOL,
	START,

	STAGE_01,
	STAGE_02,

	END,

};

enum class BRUSH_TYPE
{
	HOLLOW,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,


	END
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,

	END,
};