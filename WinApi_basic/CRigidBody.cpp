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
	// 힘의 크기
	float fForce = m_vForce.Length();

	// 힘의 방향
	m_vForce.Normalize();

	// 가속도의 크기
	float m_fAccel = fForce / m_fMass;

	// 가속도
	m_vAccel = m_vForce * m_fAccel;

	// 속도
	m_vVelocity += m_vAccel;
	
	// 속도에 따른 이동
	Move();

	// 힘 초기화
	m_vForce = vec2(0.f, 0.f);


}

void CRigidBody::Move()
{
}