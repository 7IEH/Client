#include "pch.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"

#include"CObject.h"
#include"CCamera.h"

CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
	, m_fFriCoeff(1.f)
	, m_fMaxSpeed(100.f)
	, m_fACLRT_GRVTY(9.8f)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::finalupdate()
{
	// 힘의 크기
	float fForce = m_vForce.Length();

	if (0.f != fForce) 
	{
		// 힘의 방향
		m_vForce.Normalize();

		// 가속도의 크기
		float m_fAccel = fForce / m_fMass;

		// 가속도
		m_vAccel = m_vForce * m_fAccel;

		// 속도
		m_vVelocity += m_vAccel * fDT;
	}

	// 마찰력 적용
	if (!m_vVelocity.IsZero())
	{
		vec2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();

		vec2 vFriction = vFricDir * m_fFriCoeff * fDT;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// 마찰 가속도가 본래 속도보다 더 큰 경우
			m_vVelocity = vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_pOwner->GetPos());
	vec2 vCurPos = m_pOwner->GetPos();

	if (vCurPos.y<718.f)
	{
		vec2 vFriction = vec2(0.f,4.f) * m_fACLRT_GRVTY * fDT;
		m_vVelocity += vFriction;
	}

	// 속도 제한 검사
	if (m_fMaxSpeed < m_vVelocity.Length())
	{
		m_vVelocity.Normalize();
		m_vVelocity *= m_fMaxSpeed;
	}

	// 속도에 따른 이동
	Move();

	// 힘 초기화
	m_vForce = vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	// 이동 속력
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed)
	{
		// 이동 방향
		vec2 vDir = m_vVelocity;
		vDir.Normalize();

		vec2 vPos = m_pOwner->GetPos();

		vPos += m_vVelocity * fDT;

		m_pOwner->SetPos(vPos);
	}	
}