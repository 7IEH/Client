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



	// ȭ�� �߾���ǥ�� ī�޶� LookAt ��ǥ���� ���̰� ���
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

	float fRatio = 0.f; // ����Ʈ ���� ����

	if (CAM_EFFECT::FADE_OUT == m_eEffect)
	{
		// �ð� �������� üũ�ؼ�
		m_fCurTime += fDT;

		// ���� �ð��� ����Ʈ �ִ� ���� �ð��� �Ѿ ���
		if (m_fEffectDuration < m_fCurTime)
		{
			// ȿ�� ����
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
	// ���� LookAt �� ���� Look �� ���̰��� �����ؼ� ������ LookAt �� ���Ѵ�.
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
