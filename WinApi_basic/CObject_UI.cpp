#include "pch.h"
#include "CObject_UI.h"

#include"CKeyMgr.h"

#include "SelectGDI.h"
#include "CCamera.h"

#include "CSceneMgr.h"
#include "CUIMgr.h"
#include "CScene.h"
#include "CObject_BtnUI.h"

CObject_UI::CObject_UI(bool _bCamAff)
	: m_pParentUI(nullptr)
	, m_bCamAffected(_bCamAff)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
	, m_iSQNC(0)
	, m_bSQNC(false)
	, m_ipSQNC(0)
{

}

CObject_UI::CObject_UI(const CObject_UI& _origin)
	: CObject(_origin)
	, m_pParentUI(_origin.m_pParentUI)
	, m_bCamAffected(_origin.m_bCamAffected)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
	, m_iSQNC(_origin.m_iSQNC)
	, m_bSQNC(_origin.m_bSQNC)
	, m_ipSQNC(_origin.m_iSQNC)
{
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); ++i)
	{
		AddChild(_origin.m_vecChildUI[i]->clone());
	}
}

CObject_UI::~CObject_UI()
{
	Safe_Delete_Vec(m_vecChildUI);
}

void CObject_UI::update()
{
	// child ui update
	update_child();
}

void CObject_UI::finalupdate()
{
	CObject::finalupdate();

	// UI의 최종 좌표를 구한다.
	m_vFinalPos = GetPos();

	if (GetParent())
	{
		vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}

	// UI Mouse 체크
	MouseOnCheck();
	finalupdate_child();
}

void CObject_UI::render(HDC _dc)
{
	vec2 vPos = m_vFinalPos;
	vec2 vScale = GetScale();

	if (GetParent() && m_bSQNC)
	{
		if (GetParent()->m_ipSQNC == m_iSQNC)
		{
			if (m_bCamAffected)
			{
				vPos = CCamera::GetInst()->GetRenderPos(vPos);
			}

			if (m_bLbtnDown)
			{
				SelectGDI select(_dc, PEN_TYPE::GREEN);

				Rectangle(_dc
					, int(vPos.x)
					, int(vPos.y)
					, int(vPos.x + vScale.x)
					, int(vPos.y + vScale.y));
			}
			else
			{
				Rectangle(_dc
					, int(vPos.x)
					, int(vPos.y)
					, int(vPos.x + vScale.x)
					, int(vPos.y + vScale.y));
			}
		}
	}
	else
	{
		if (m_bCamAffected)
		{
			vPos = CCamera::GetInst()->GetRenderPos(vPos);
		}

		if (m_bLbtnDown)
		{
			SelectGDI select(_dc, PEN_TYPE::GREEN);

			Rectangle(_dc
				, int(vPos.x)
				, int(vPos.y)
				, int(vPos.x + vScale.x)
				, int(vPos.y + vScale.y));
		}
		else
		{
			Rectangle(_dc
				, int(vPos.x)
				, int(vPos.y)
				, int(vPos.x + vScale.x)
				, int(vPos.y + vScale.y));
		}
	}

	// child ui render
	render_child(_dc);
}

void CObject_UI::MouseOn()
{
}

void CObject_UI::MouseLbtnDown()
{
}

void CObject_UI::MouseLbtnUp()
{
}

void CObject_UI::MouseLbtnClicked()
{
}

void CObject_UI::update_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
	}
}

void CObject_UI::finalupdate_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->finalupdate();
	}
}

void CObject_UI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CObject_UI::MouseOnCheck()
{
	vec2 vMousePos = MOUSE_POS;
	vec2 vScale = GetScale();


	if (m_bCamAffected)
	{
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	}

	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}
