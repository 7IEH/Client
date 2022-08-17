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
	, m_eEffect(CAM_EFFECT::NONE)
	, m_pVeilTex(nullptr)
	, m_fEffectDuration(0.f)
	, m_fCurTime(0.f)
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
	}
	/*
	if (KEY_CHECK(X, TAP))
	{
		FadeIn();
	}*/

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

	if (CAM_EFFECT::NONE == m_eEffect)
		return;

	float fRatio = 0.f; // 이펙트 진행 비율

	if (CAM_EFFECT::FADE_OUT == m_eEffect)
	{
		// 시간 누적값을 체크해서
		m_fCurTime += fDT;

		// 진행 시간이 이펙트 최대 지정 시간을 넘어선 경우
		if (m_fEffectDuration < m_fCurTime)
		{
			// 효과 종료
			m_eEffect=CAM_EFFECT::NONE;
			return;
		}

		fRatio = m_fCurTime / m_fEffectDuration;
	}

	int iAlpha = (int)(255.f * fRatio);

	/*if (CAM_EFFECT::FADE_IN == m_eEffect)
		return;*/

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
