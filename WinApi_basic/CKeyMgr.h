#pragma once

#include "pch.h"

// 1. 프레임 동기화
// 동일 프레임 내에서 같은 키에 대해, 동일한 이벤트를 가져간다.

// 2. 키 입력 이벤트 처리
// tap, hold, away


enum class KEY_STATE
{
	NONE,   //안 눌려 있는 상태
	TAP,	      // 막 누른 시점
	HOLD,   // 누르고 있는
	AWAY,   // 막 뗀 시점
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
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
	Z,
	X,
	C,
	V,
	B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LAST,
};

struct tKeyInfo
{
	KEY_STATE		eState;  // 키 의 상태값
	bool				bPrevPush;    // 이전 프레임에서 눌렀는지 여부
};

class CKeyMgr
{
public:
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo> m_vecKey;

public:
	void init();
	void update();
public:
	KEY_STATE GetKeyState(KEY _key) { return m_vecKey[(int)_key].eState; }
};

