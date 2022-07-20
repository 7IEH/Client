#include "pch.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CCollider.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
	, m_bAlive(true)
{
}

CObject::~CObject() 
{
	if (nullptr != m_pCollider)
		delete m_pCollider;
}

void CObject::update()
{
	
}

void CObject::finalupdate()
{
	if (m_pCollider)
		m_pCollider->finalupdate();
}

void CObject::render(HDC _dc)
{
	Rectangle(_dc,
		(int)(m_vPos.x - m_vScale.x / 2),
		(int)(m_vPos.y - m_vScale.y / 2),
		(int)(m_vPos.x + m_vScale.x / 2),
		(int)(m_vPos.y + m_vScale.y / 2));

	component_Render(_dc);
}

void CObject::component_Render(HDC _dc)
{
	if (m_pCollider != nullptr)
	{
		m_pCollider->render(_dc);
	}
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}