#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CObject_BtnUI.h"
#include "CTexture.h"

#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CUIMgr.h"

CObject_BtnUI::CObject_BtnUI()
	: CObject_UI(false)
	, m_pFunc(nullptr)
	, m_pFunc2(nullptr)
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

		if (GetParent())
		{
			vCurPos = GetFinalPos();
		}

		if (GetParent() && GetbSQNC())
		{
			if (GetParent()->GetpSQNC()==GetSQNC())
			{
				BLENDFUNCTION bf = {};

				bf.BlendOp = AC_SRC_OVER;
				bf.BlendFlags = 0;
				bf.AlphaFormat = AC_SRC_ALPHA;
				bf.SourceConstantAlpha = 127;

				AlphaBlend(_dc
					, (int)(vCurPos.x)
					, (int)(vCurPos.y)
					, Width, Height
					, m_pTex->GetDC()
					, 0, 0, Width, Height
					, bf);
			}
		}
		else
		{
			BLENDFUNCTION bf = {};

			bf.BlendOp = AC_SRC_OVER;
			bf.BlendFlags = 0;
			bf.AlphaFormat = AC_SRC_ALPHA;
			bf.SourceConstantAlpha = 127;

			AlphaBlend(_dc
				, (int)(vCurPos.x)
				, (int)(vCurPos.y)
				, Width, Height
				, m_pTex->GetDC()
				, 0, 0, Width, Height
				, bf);
		}
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
	if (IsLbtnDown() && this->GetName()==L"Start_button")
	{
		CTexture* _pTex = CResMgr::GetInst()->LoadTexture(L"startbutton2", L"texture\\startbutton2.bmp");
		this->SetTexture(_pTex);
	}
	if (IsLbtnDown() && this->GetName() == L"Tool_button")
	{
		CTexture* _pTex = CResMgr::GetInst()->LoadTexture(L"toolbutton2", L"texture\\toolbutton2.bmp");
		this->SetTexture(_pTex);
	}
	if (IsLbtnDown() && this->GetName() == L"Exit_button")
	{
		CTexture* _pTex = CResMgr::GetInst()->LoadTexture(L"exitbutton2", L"texture\\exitbutton2.bmp");
		this->SetTexture(_pTex);
	}
}

void CObject_BtnUI::MouseLbtnDown()
{
}


void CObject_BtnUI::MouseLbtnUp()
{
	if (this->GetName() == L"Start_button")
	{
		CTexture* _pTex = CResMgr::GetInst()->LoadTexture(L"startbutton", L"texture\\startbutton.bmp");
		this->SetTexture(_pTex);
	}
	if (this->GetName() == L"Tool_button")
	{
		CTexture* _pTex = CResMgr::GetInst()->LoadTexture(L"toolbutton", L"texture\\toolbutton.bmp");
		this->SetTexture(_pTex);
	}
	if (this->GetName() == L"Exit_button")
	{
		CTexture* _pTex = CResMgr::GetInst()->LoadTexture(L"exitbutton", L"texture\\exitbutton.bmp");
		this->SetTexture(_pTex);
	}
}

void CObject_BtnUI::MouseLbtnClicked()
{
	if (nullptr != m_pFunc2)
	{
		m_pFunc2(m_param3);
	}

	if (nullptr != m_pFunc)
	{
		m_pFunc(m_param1, m_param2);
	}

	if (m_pSceneInst && m_pSceneFunc)
	{
		((*m_pSceneInst).*m_pSceneFunc)();
	}
}
