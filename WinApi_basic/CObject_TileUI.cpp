#include "pch.h"
#include "CObject_TileUI.h"
#include "CObject_Tile.h"

#include "CKeyMgr.h"
#include "CTexture.h"

#include "CSceneMgr.h"
#include "CScene.h"


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
	if (IsLbtnDown())
	{
		vec2 vDiff = MOUSE_POS - m_vDragStart;

		vec2 vCurPos = GetPos();
		vCurPos += vDiff;
		SetPos(vCurPos);

		m_vDragStart = MOUSE_POS;
	}
}

void CObject_TileUI::MouseLbtnDown()
{
	m_vDragStart = MOUSE_POS;
}

void CObject_TileUI::MouseLbtnUp()
{
	vec2 vCurPos = MOUSE_POS;
	CScene* CurScene = CSceneMgr::GetInst()->GetCurScene();

	vCurPos = vCurPos/64.f;
	vCurPos.x = (int)vCurPos.x;
	vCurPos.y = (int)vCurPos.y;
	vCurPos *= 64.f;
	vCurPos += 32.f;

	CObject_Tile* _pTile = new CObject_Tile;
	_pTile->SetPos(vCurPos);
	_pTile->SetTexture(m_pTex);
	_pTile->SetScale(vec2(64.f, 64.f));
	_pTile->SetName(L"¿Ö»ý¼º¾ÈµÅ");
	CurScene->pushObject((UINT)GROUP_TYPE::TILE,_pTile);
}

