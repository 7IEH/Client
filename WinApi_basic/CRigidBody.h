#pragma once

class CRigidBody
{
private:
	CObject*	m_pOwner;

	vec2			m_vForce;			// 크기, 방향
	vec2			m_vAccel;			// 가속도
	float			m_fMass;			// 질량

	vec2			m_vVelocity;		// 속도 ( 크기 : 속력, 방향)
	float			m_fMass;			// 질량

	// F = M * A
	// V+= A * DT

public:
	void finalupdate();

public:
	void AddForce(vec2 _vF)
	{
		m_vForce += _vF;
	}

	void SetMass(float _fMass) { m_fMass = _fMass; }

	float GetMass() { return m_fMass; }
private:
	void Move();

public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

