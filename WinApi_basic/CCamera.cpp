#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(0.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.5f)
{
}

CCamera::~CCamera()
{
}

void CCamera::update()
{
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
		m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
	}

	vec2 vResuloution = CCore::GetInst()->GetResolution();
	vec2 vCenter = vResuloution / 2;

	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;
}
