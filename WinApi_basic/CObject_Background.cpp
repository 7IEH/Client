#include "pch.h"
#include "CObject_Background.h"
#include "CResMgr.h"
#include "CTexture.h"

CObject_Background::CObject_Background()
	:m_pTex(nullptr)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"BackgroundTex", L"texture\\Background.bmp");
}

CObject_Background::~CObject_Background()
{
}

void CObject_Background::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	BitBlt(_dc
		, 0
		, 0
		, iWidth
		, iHeight
		, m_pTex->GetDC()
		, 0, 0, SRCCOPY);
}