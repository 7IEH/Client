#pragma once

#define fDT CTimeMgr::GetInst()->GETfDT()
#define DT CTimeMgr::GetInst()->GetDT()
#define KEY_CHECK(key,state) CKeyMgr::GetInst()->GetKeyState(KEY::key) == KEY_STATE::state


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

enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	MISSILE,
	MONSTER,


	END=32,
};


enum class SCENE_TYPE
{
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