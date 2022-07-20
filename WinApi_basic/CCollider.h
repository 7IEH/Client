#pragma once

class CObject;

class CCollider
{
private:
	static	UINT g_iNextID;

	CObject*	m_pOwner;				// collider 를 소유하고 있는 오브젝트
	vec2			m_vOffsetPos;			// 오브젝트로 부터 상대적인 위치
	vec2			m_vFinalPos;				// finalupdate에서 매 프레임마다 갱신

	vec2			m_vScale;					// 충돌체 크기

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
	// 충돌 시점 함수
	void OnCollision(CCollider* _pOther); // 충돌 중인 경우 호출되는 함수
	void OnCollisionEnter(CCollider* _pOther); // 막 충돌한 경우 호출되는 함수
	void OnCollisionExit(CCollider* _pOther);

	CCollider& operator=(CCollider& _origin) = delete;

public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();
	friend class CObject;
};

