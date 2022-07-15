#pragma once


class CCollider;

class CObject
{
private:
	vec2       m_vPos;
	vec2       m_vScale;

	CCollider* m_pCollider;

public:
	void SetPos(vec2 _vPos) 
	{
		m_vPos = _vPos;
	}
	vec2 GetPos() 
	{
		return m_vPos;
	}
	void SetScale(vec2 _vScale) 
	{
		m_vScale = _vScale;
	}
	vec2 GetScale() 
	{
		return m_vScale;
	}

	void CreateCollider();
	CCollider* GetCollider() { return m_pCollider; }

public:
	virtual void update();
	virtual void finalupdate()final;
	virtual void render(HDC _dc);

	void component_Render(HDC _dc);

public:
	CObject();
	virtual ~CObject();
};

