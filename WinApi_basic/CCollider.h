#pragma once

class CObject;

class CCollider
{
private:
	static	UINT g_iNextID;

	CObject*	m_pOwner;				// collider �� �����ϰ� �ִ� ������Ʈ
	vec2			m_vOffsetPos;			// ������Ʈ�� ���� ������� ��ġ
	vec2			m_vFinalPos;				// finalupdate���� �� �����Ӹ��� ����

	vec2			m_vScale;					// �浹ü ũ��

	UINT			m_iID;
	UINT			m_iCol;

public:
	void SetOffsetPos(vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(vec2 _vScale) { m_vScale = _vScale; }

	vec2 GetOffsetPos() { return m_vOffsetPos; }
	vec2 GetScale() { return m_vScale; }

	vec2 GetFinalPos() { return m_vFinalPos; }
	
	CObject* GetObj() { return m_pOwner; }
	UINT GetID() { return m_iID; }

public:
	void finalupdate();
	void render(HDC _dc);

public:
	// �浹 ���� �Լ�
	void OnCollision(CCollider* _pOther); // �浹 ���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(CCollider* _pOther); // �� �浹�� ��� ȣ��Ǵ� �Լ�
	void OnCollisionExit(CCollider* _pOther);

	CCollider& operator=(CCollider& _origin) = delete;

public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();
	friend class CObject;
};

