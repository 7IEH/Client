#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;

	vec2			m_vForce;							// 크기, 방향
	vec2			m_vAccel;							// 가속도
	vec2			m_vVelocity;						// 속도 ( 크기 : 속력, 방향)

	float			m_fMass;							// 질량
	float			m_fMaxSpeed;					// 최대 속력
	float			m_fFriCoeff;						// 마찰 계수

	float			m_fACLRT_GRVTY;				//중력 가속도
	// F = M * A
	// V += A * DT(내 현재속도)

public:
	void finalupdate();

public:
	void AddForce(vec2 _vF)
	{
		m_vForce += _vF;
	}
	void SetMass(float _fMass) { m_fMass = _fMass; }
	void SetMaxSpeed(float _fMaxVelocity) { m_fMaxSpeed = _fMaxVelocity; }
	void AddVelocity(vec2 _v) { m_vVelocity += _v; }

	float GetMaxSpeed() { return m_fMaxSpeed; }
	float GetMass() { return m_fMass; }

private:
	void Move();
	void Jump();

public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

