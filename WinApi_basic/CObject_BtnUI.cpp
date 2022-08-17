#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CObject_BtnUI.h"


CObject_BtnUI::CObject_BtnUI()
	: CObject_UI(false)
	, m_pFunc(nullptr)
	, m_param1(0)
	, m_param2(0)
	, m_pSceneInst(nullptr)
	, m_pSceneFunc(nullptr)
{
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
