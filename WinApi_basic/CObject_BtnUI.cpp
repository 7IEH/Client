#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CObject_BtnUI.h"
#include "CTexture.h"

CObject_BtnUI::CObject_BtnUI()
	: CObject_UI(false)
	, m_pFunc(nullptr)
	, m_param1(0)
	, m_param2(0)
	, m_pSceneInst(nullptr)
	, m_pSceneFunc(nullptr)
	, m_pTex(nullptr)
{
}

void CObject_BtnUI::render(HDC _dc)
{
	if (nullptr != m_pTex)
	{
		vec2 vCurPos = GetPos();
		int Width = m_pTex->Width();
		int Height = m_pTex->Height();


		BitBlt(_dc
			, (int)vCurPos.x
			, (int)vCurPos.y
			, Width
			, Height
			, m_pTex->GetDC()
			, 0
			, 0
			, SRCCOPY);
	}
	else 
	{
		CObject_UI::render(_dc);
	}
}

CObject_BtnUI::~CObject_BtnUI()
{
}

void CObject_BtnUI::MouseOn()
{
}

void CObject_BtnUI::MouseLbtnDown()
{
}

void CObject_BtnUI::MouseLbtnUp()
{
}

void CObject_BtnUI::MouseLbtnClicked()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_param1, m_param2);
	}

	if (m_pSceneInst && m_pSceneFunc)
	{
		((*m_pSceneInst).*m_pSceneFunc)();
	}
}
