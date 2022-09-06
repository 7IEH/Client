#include "pch.h"
#include "CObject_TextUI.h"

CObject_TextUI::CObject_TextUI()
	: CObject_UI(false)
{
}

CObject_TextUI::~CObject_TextUI()
{
}

void CObject_TextUI::update()
{
}

void CObject_TextUI::render(HDC _dc)
{
	vec2 vCurPos = GetPos();

	TextOut(_dc,(int)vCurPos.x,(int)vCurPos.y, m_Str.c_str(), (int)m_Str.size());
}