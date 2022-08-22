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
	// ���� ũ��
	float fForce = m_vForce.Length();

	if (0.f != fForce) 
	{
		// ���� ����
		m_vForce.Normalize();

		// ���ӵ��� ũ��
		float m_fAccel = fForce / m_fMass;

		// ���ӵ�
		m_vAccel = m_vForce * m_fAccel;

		// �ӵ�
		m_vVelocity += m_vAccel * fDT;
	}

	// ������ ����
	if (!m_vVelocity.IsZero())
	{
		vec2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();

		vec2 vFriction = vFricDir * m_fFriCoeff * fDT;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// ���� ���ӵ��� ���� �ӵ����� �� ū ���
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

	// �ӵ� ���� �˻�
	if (m_fMaxSpeed < m_vVelocity.Length())
	{
		m_vVelocity.Normalize();
		m_vVelocity *= m_fMaxSpeed;
	}

	// �ӵ��� ���� �̵�
	Move();

	// �� �ʱ�ȭ
	m_vForce = vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	// �̵� �ӷ�
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed)
	{
		// �̵� ����
		vec2 vDir = m_vVelocity;
		vDir.Normalize();

		vec2 vPos = m_pOwner->GetPos();

		vPos += m_vVelocity * fDT;

		m_pOwner->SetPos(vPos);
	}	
}