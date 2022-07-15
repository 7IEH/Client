#pragma once

class CObject;

class CCollider
{
private:
	CObject*	m_pOwner;				// collider 를 소유하고 있는 오브젝트
	vec2			m_vOffsetPos;			// 오브젝트로 부터 상대적인 위치
	vec2			m_vFinalPos;				// finalupdate에서 매 프레임마다 갱신

	vec2			m_vScale;					// 충돌체 크기

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

