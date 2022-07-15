#include "pch.h"
#include "CObject_Monster.h"

#include "CTimeMgr.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CObject_Missile.h"
#include "CTexture.h"
#include"CResMgr.h"
#include "CCollider.h"

CObject_Monster::CObject_Monster()
	:m_fSpeed(100.f)
	,m_vCenterPos(vec2(0.f,0.f))
	,m_fMaxDistance(100.f)
	,m_iDir(1)
	,m_mTex(nullptr)
{
	// texture 积己
	m_mTex = CResMgr::GetInst()->LoadTexture(L"MonsterTex", L"texture\\enemy.bmp");

	// collider component 积己
	CreateCollider();
	GetCollider()->SetScale(vec2(50.f, 50.f));
}

CObject_Monster::~CObject_Monster()
{
}

void CObject_Monster::update()
{
	vec2 vCurPos = GetPos();

	if (m_iDir > 0 ) 
	{
		vCurPos.x += GetSpeed() * fDT;
		if (m_vCenterPos.x + m_fMaxDistance < vCurPos.x) {
			m_iDir = -1;
			createMissile();
		}
	}

	if (m_iDir < 0)
	{
		vCurPos.x -= GetSpeed() * fDT;
		if (m_vCenterPos.x - m_fMaxDistance > vCurPos.x) {
			m_iDir = 1;
			createMissile();
		}
	}
	SetPos(vCurPos);
}

void CObject_Monster::render(HDC _dc) 
{
	int iWidth = (int)m_mTex->Width();
	int iHeight = (int)m_mTex->Height();
	BitBlt(_dc
		, (int)(GetPos().x - float(iWidth / 2))
		, (int)(GetPos().y - float(iHeight / 2))
		, iWidth, iHeight
		, m_mTex->GetDC()
		, 0, 0, SRCCOPY);

	// 阁胶磐 按眉 component render
	component_Render(_dc);
}

void CObject_Monster::createMissile()
{
	vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	CObject_Missile* miObj = new CObject_Missile;
	miObj->SetPos(vMissilePos);
	miObj->SetScale(vec2(10.f, 10.f));
	miObj->SetTheta(-270.f);

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->pushObject((UINT)GROUP_TYPE::MISSILE, miObj);
}
