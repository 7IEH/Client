#include "pch.h"

#include "CEventMgr.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CObject.h"

CEventMgr::CEventMgr()
	:m_vecEvent{}
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::update()
{
	// ===========================
	// 이전 프레임에서 등록해둔 Dead Object 들을 삭제한다.
	// ===========================

	for (size_t i= 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	// ==========
	// Event 처리
	// ==========

	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventMgr::Excute(const tEvent& _eve)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
		// lparam : object address
		// wparam : group type
	{
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;
		pCurScene->pushObject((UINT)eType, pNewObj);
	}
		break;

	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lparam : object address
		// object 를 Dead  상태로 변경
		// 삭제 예정 오브젝트들을 모아둔다.
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
		break;

	case EVENT_TYPE::SCENE_CHANGE:
		break;

	case EVENT_TYPE::END:
		break;

	default:
		break;
	}
}
