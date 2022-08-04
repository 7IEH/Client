#include "pch.h"
#include "Background_Title.h"

#include"CResMgr.h"
#include"CTexture.h"

Background_Title::Background_Title()
	:m_pTex(nullptr)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"TitleTex", L"texture\\Title.bmp");
}

Background_Title::~Background_Title()
{

}

void Background_Title::render(HDC _dc)
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