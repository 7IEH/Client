#include "pch.h"
#include "CObject_TileUI.h"
#include "CKeyMgr.h"
#include "CTexture.h"

CObject_TileUI::CObject_TileUI()
	: CObject_UI(false)
	, m_pTex(nullptr)
{
}

CObject_TileUI::~CObject_TileUI()
{
}


void CObject_TileUI::render(HDC _dc)
{
	if (nullptr != m_pTex)
	{
		vec2 vCurPos = GetPos();
		int Width = m_pTex->Width();
		int Height = m_pTex->Height();

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
	else
	{
		vec2 scacle = GetScale();
		CObject_UI::render(_dc);
	}
}

void CObject_TileUI::MouseOn()
{
	m_vDragStart = MOUSE_POS;
	if (IsMouseOn())
	{
		vec2 m_vDiff = MOUSE_POS - m_vDragStart;

		vec2 vCurPos = GetPos();
		vCurPos += m_vDiff;
		SetPos(vCurPos);
		m_vDragStart = MOUSE_POS;
	}
}

