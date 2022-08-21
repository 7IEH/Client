#include "pch.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"

CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(0.f)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::finalupdate()
{
	m_vForce;
	// ���� ũ��
	float fForce = m_vForce.Length();

	// ���� ����
	m_vForce.Normalize();

	// ���ӵ��� ũ��
	float m_fAccel = fForce / m_fMass;

	// ���ӵ�
	m_vAccel = m_vForce * m_fAccel;

	// �ӵ�
	m_vVelocity += m_vAccel;
	
	// �ӵ��� ���� �̵�
	Move();

	// �� �ʱ�ȭ
	m_vForce = vec2(0.f, 0.f);


}

void CRigidBody::Move()
{
}