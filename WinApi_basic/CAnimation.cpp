#include "pch.h"
#include "CAnimation.h"

#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CObject.h"
#include "CTexture.h"
#include "CCamera.h"

CAnimation::CAnimation()
	:m_pAnimator(nullptr)
	,m_pTex(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	,m_bFinsih(false)
{

}

CAnimation::~CAnimation()
{

}

void CAnimation::update()
{

	if (m_bFinsih)
		return;

	m_fAccTime += fDT;

	if (m_vecFrm[m_iCurFrm].fDuration<m_fAccTime )
	{
		++m_iCurFrm;
		
		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;
			m_bFinsih = true;
			m_fAccTime = 0.f;
			return;
		}
		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;
	}
}


void CAnimation::Create(CTexture* _pTex, vec2 _vLT, vec2 _vSliceSize, vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};
	for(UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT+_vStep	*	i;

		m_vecFrm.push_back(frm);
	}
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinsih)
		return;

	CObject* pObj = m_pAnimator->GetObj();
	vec2 vPos = pObj->GetPos();

	vPos += m_vecFrm[m_iCurFrm].vOffset; // Object Postion 에 Offset 만큼 추가 이동 위치

	// 렌더링 좌표로 변환
	vPos = RENDERPOS(vPos);

	TransparentBlt(_dc
		, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)
		, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)
		, (int)m_vecFrm[m_iCurFrm].vSlice.x
		, (int)m_vecFrm[m_iCurFrm].vSlice.y
		, m_pTex->GetDC()
		, (int)m_vecFrm[m_iCurFrm].vLT.x
		, (int)m_vecFrm[m_iCurFrm].vLT.y
		, (int)m_vecFrm[m_iCurFrm].vSlice.x
		, (int)m_vecFrm[m_iCurFrm].vSlice.y
		, RGB(255, 128, 128)
	);
}



