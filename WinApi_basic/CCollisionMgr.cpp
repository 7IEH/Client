#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"

#include "CObject.h"
#include "CScene.h"

CCollisionMgr::CCollisionMgr()
	:m_vLeftGroup()
	,m_vRightGroup()
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::init()
{

}

void CCollisionMgr::update()
{
	/*for (auto monster : m_vRightGroup)
	{
		if()
	}*/
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	m_vLeftGroup=pCurScene->vGetObject(_eLeft);
	m_vRightGroup =pCurScene->vGetObject(_eRight);
}

