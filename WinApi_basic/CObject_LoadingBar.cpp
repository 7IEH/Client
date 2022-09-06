#include "pch.h"
#include "CObject_LoadingBar.h"
#include "CTexture.h"
#include "CResMgr.h"

CObject_LoadingBar::CObject_LoadingBar()
	: m_iprocess(0)
{
	m_pTex=CResMgr::GetInst()->LoadTexture(L"LoadingBar", L"texture\\Loading.bmp");
}

CObject_LoadingBar::~CObject_LoadingBar()
{
}

void CObject_LoadingBar::render(HDC _dc)
{
	vec2 vCurPos = GetPos();
	int Width = m_pTex->Width();
	int Height = m_pTex->Height();

	BitBlt(
		  _dc
		, (int)(vCurPos.x - Width/2)
		, (int)(vCurPos.y - Height/2)
		, (int) 200 * m_iprocess
		, Height
		, m_pTex->GetDC()
		, 0, 0, SRCCOPY);
}