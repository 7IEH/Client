#include "pch.h"
#include "CObject_ImgUI.h"

#include "CTexture.h"

CObject_ImgUI::CObject_ImgUI()
	: CObject_UI(false)
	, m_pTex(nullptr)
{
}

CObject_ImgUI::~CObject_ImgUI()
{
}


void CObject_ImgUI::render(HDC _dc)
{
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 127;

	vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	float width = m_vRB.x - m_vLT.x;
	float height = m_vRB.y - m_vLT.y;


	BitBlt(_dc
		, (int)vPos.x
		, (int)vPos.y
		, (int)width
		, (int)height
		, m_pTex->GetDC()
		, (int)m_vLT.x
		, (int)m_vLT.y
		, SRCCOPY
	);
	
	//?? ¿Ö ¾ÈµÇÂ¡
	/*
	AlphaBlend(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, (int)(width), int(height)
		, m_pTex->GetDC()
		, (int)m_vLT.x,(int)m_vLT.y, (int)m_vRB.x, (int)m_vRB.y
		, bf);
		*/
}