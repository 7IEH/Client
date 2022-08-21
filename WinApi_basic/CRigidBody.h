#pragma once

class CRigidBody
{
private:
	CObject*	m_pOwner;

	vec2			m_vForce;			// ũ��, ����
	vec2			m_vAccel;			// ���ӵ�
	float			m_fMass;			// ����

	vec2			m_vVelocity;		// �ӵ� ( ũ�� : �ӷ�, ����)
	float			m_fMass;			// ����

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

