#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include"CResMgr.h"

#include"CTexture.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(0.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.5f)
	, m_pVeilTex(nullptr)
{
}

CCamera::~CCamera()
{
}

void CCamera::update()
{
	if(KEY_CHECK(Z, TAP))
	{
		FadeOut(10.f);
		FadeIn(10.f);
	}

	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	if (KEY_CHECK(UP, HOLD))
		m_vLookAt.y -= 500.f * fDT;
	if (KEY_CHECK(DOWN, HOLD))
		m_vLookAt.y += 500.f * fDT;
	if (KEY_CHECK(LEFT, HOLD))
		m_vLookAt.x -= 500.f * fDT;
	if (KEY_CHECK(RIGHT, HOLD))
		m_vLookAt.x += 500.f * fDT;



	// 화면 중앙좌표와 카메라 LookAt 좌표간의 차이값 계산
	CalDiff();
}

void CCamera::init()
{
	vec2 vResolution = CCore::GetInst()->GetResolution();
	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"cameraVeil",(UINT)vResolution.x, (UINT)vResolution.y);
}

void CCamera::render(HDC _dc)
{
	if (m_vecCamEffect.empty())
		return;


	tCamEffect& effect = m_vecCamEffect.front();
	effect.m_fCurTime += fDT;

	float fRatio = 0.f; // 이펙트 진행 비율
	fRatio = effect.m_fCurTime / effect.m_fDuration;
	
	if (fRatio < 0.f)
		fRatio = 0.f;
	if (fRatio > 1.f)
		fRatio = 1.f;

	int iAlpha = 0;

	if (CAM_EFFECT::FADE_OUT == effect.eEffect)
	{
		iAlpha = (int)(255.f * fRatio);
	}
	else if (CAM_EFFECT::FADE_IN == effect.eEffect)
	{
		iAlpha = (int)(255.f * (1.f-fRatio));
	}

	if (CAM_EFFECT::NONE == m_vecCamEffect.front().eEffect)
	{
		m_vecCamEffect.erase(m_vecCamEffect.begin());
		return;
	}

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha;

	vec2 vResolution = CCore::GetInst()->GetResolution();

	AlphaBlend(_dc
		, 0
		, 0
		, (int)(vResolution.x), int(vResolution.y)
		, m_pVeilTex->GetDC()
		, 0, 0, (int)vResolution.x, (int)vResolution.y
		, bf);

	// 진행 시간이 이펙트 최대 지정 시간을 넘어선 경우
	if (effect.m_fDuration < effect.m_fCurTime)
	{
		// 효과 종료
		m_vecCamEffect.erase(m_vecCamEffect.begin());
	}
}

void CCamera::CalDiff()
{
	// 이전 LookAt 과 현재 Look 의 차이값을 보정해서 현재의 LookAt 을 구한다.
	m_fAccTime += fDT;

	if (m_fTime<= m_fAccTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		vec2 vLookDir = m_vLookAt - m_vPrevLookAt;

		if (!vLookDir.IsZero())
		{
			m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
		}
	}

	vec2 vResuloution = CCore::GetInst()->GetResolution();
	vec2 vCenter = vResuloution / 2;

	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;
}
