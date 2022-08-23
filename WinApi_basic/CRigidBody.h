#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;

	vec2			m_vForce;							// ũ��, ����
	vec2			m_vAccel;							// ���ӵ�
	vec2			m_vVelocity;						// �ӵ� ( ũ�� : �ӷ�, ����)

	float			m_fMass;							// ����
	float			m_fMaxSpeed;					// �ִ� �ӷ�
	float			m_fFriCoeff;						// ���� ���

	float			m_fACLRT_GRVTY;				//�߷� ���ӵ�
	// F = M * A
	// V += A * DT(�� ����ӵ�)

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

