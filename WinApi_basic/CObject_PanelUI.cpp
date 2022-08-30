#include "pch.h"
#include "CObject_PanelUI.h"

#include "CKeyMgr.h"

CObject_PanelUI::CObject_PanelUI()
	: CObject_UI(false)
{

}

CObject_PanelUI::~CObject_PanelUI()
{

}


void CObject_PanelUI::update()
{



}

void CObject_PanelUI::MouseOn()
{
	if (IsLbtnDown())
	{
		vec2 vDiff = MOUSE_POS - m_vDragStart;

		vec2 vCurPos = GetPos();
		vCurPos += vDiff;
		SetPos(vCurPos);

		m_vDragStart = MOUSE_POS;
	}
	int a = 3;
}

void CObject_PanelUI::MouseLbtnDown()
{
	m_vDragStart = MOUSE_POS;
}

void CObject_PanelUI::MouseLbtnUp()
{

}