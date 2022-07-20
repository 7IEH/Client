#pragma once


class CCollider;

class CObject
{
private:
	wstring		m_strName;

	vec2			 m_vPos;
	vec2			 m_vScale;

	CCollider*	 m_pCollider;

	bool			 m_bAlive;

public:
	void SetName(const wstring _strName)	{ m_strName = _strName; }
	const wstring& GetName()	{ return m_strName; }		

	void SetPos(vec2 _vPos) {	m_vPos = _vPos; }
	vec2 GetPos() { return m_vPos; }

	void SetScale(vec2 _vScale) { m_vScale = _vScale; }
	vec2 GetScale() { return m_vScale; }	

	bool IsDead() { return !m_bAlive; }
	

	void CreateCollider();
	CCollider* GetCollider() { return m_pCollider; }

	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

private:
	void SetDead() { m_bAlive = false; }

public:
	virtual void update();
	virtual void finalupdate()final;
	virtual void render(HDC _dc);

	void component_Render(HDC _dc);

public:
	CObject();
	virtual ~CObject();

	friend class CEventMgr;
};

