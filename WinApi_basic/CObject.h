#pragma once

#include "CCamera.h"

class CCollider;
class CAnimator;
class CRigidBody;

class CObject
{
private:
	wstring				m_strName;

	vec2					m_vPos;
	vec2					m_vScale;

	// component;
	CCollider*			m_pCollider;
	CAnimator*		m_pAnimator;
	CRigidBody*		m_pRigidBody;

	bool					m_bAlive;
	bool					m_bOnFloor;

public:
	void SetName(const wstring _strName)	{ m_strName = _strName; }
	const wstring& GetName()	{ return m_strName; }		

	void SetPos(vec2 _vPos) {	m_vPos = _vPos; }
	vec2 GetPos() { return m_vPos; }

	void SetScale(vec2 _vScale) { m_vScale = _vScale; }
	vec2 GetScale() { return m_vScale; }	

	bool IsDead() { return !m_bAlive; }
	
	void SetOnFloor(bool _bOnFloor) { m_bOnFloor = _bOnFloor; }
	bool GetOnFloor() { return m_bOnFloor; }
	
	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();

	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; }

	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

private:
	void SetDead() { m_bAlive = false; }

public:
	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	void component_Render(HDC _dc);


	// 나 자신의 복제버전을 되돌려 주는 역할
	virtual CObject* clone() = 0;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

	friend class CEventMgr;
};

