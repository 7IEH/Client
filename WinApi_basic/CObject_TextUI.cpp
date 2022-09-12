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
	if (GetParent())
	{
		vCurPos = GetFinalPos();
	}

	if (GetParent() && GetbSQNC())
	{
		if (GetParent()->GetpSQNC() == GetSQNC())
		{
			SetBkMode(_dc, TRANSPARENT);
			TextOut(_dc, (int)vCurPos.x, (int)vCurPos.y, m_Str.c_str(), (int)m_Str.size());
		}
	}
	else
	{
		SetBkMode(_dc, TRANSPARENT);
		TextOut(_dc, (int)vCurPos.x, (int)vCurPos.y, m_Str.c_str(), (int)m_Str.size());
	}
}