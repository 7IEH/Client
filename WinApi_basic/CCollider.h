#pragma once

class CObject;

class CCollider
{
private:
	CObject*	m_pOwner;				// collider �� �����ϰ� �ִ� ������Ʈ
	vec2			m_vOffsetPos;			// ������Ʈ�� ���� ������� ��ġ
	vec2			m_vFinalPos;				// finalupdate���� �� �����Ӹ��� ����

	vec2			m_vScale;					// �浹ü ũ��

public:
	void SetOffsetPos(vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(vec2 _vScale) { m_vScale = _vScale; }

	vec2 SetOffsetPos() { return m_vOffsetPos; }
	vec2 SetScale() { return m_vScale; }

public:
	void finalupdate();
	void render(HDC _dc);

public:
	CCollider();
	~CCollider();
	friend class CObject;
};

