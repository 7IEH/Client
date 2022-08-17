#include "pch.h"
#include "CUIMgr.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject_UI.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	// 1. FocusedUI 확인
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
		return;

	// 2. FocusedUI 내에서, 부모 UI 포함, 자식 UI 들 중 실제 타겟팅 된 UI 를 가져온다.
	CObject_UI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	bool bLbtnTap = KEY_CHECK(LBTN, TAP);
	bool bLbtnAway = KEY_CHECK(LBTN, AWAY);

	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();

		if (bLbtnTap)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway)
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbtnDown)
			{
				pTargetUI->MouseLbtnClicked();
			}

			// 왼쪽버튼 떼면, 눌렀던 체크를 다시 해제한다.
			pTargetUI->m_bLbtnDown = false;
		}
	}
}

void CUIMgr::SetFocusedUI(CObject_UI* _pUI)
{
	// 이미 포커싱 중인 경우 or 포커싱 해제요청인 경우
	if (m_pFocusedUI == _pUI || nullptr == _pUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}

	m_pFocusedUI = _pUI;

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter < vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	// 백터 내에서 맨 뒤로 순번 교체
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}

CObject_UI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_CHECK(LBTN, TAP);

	// 기존 포커싱 UI를 받아두고 변경되었는지 확인한다.
	CObject_UI* pFocusedUI = m_pFocusedUI;

	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	// 왼쪽버튼 TAP 이 발생한 상황
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter < vecUI.end(); ++iter)
	{
		if (((CObject_UI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}
	
	// 이번에 Focus 된 UI가 없다.
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusedUI = (CObject_UI*)*targetiter;

	// 백터 내에서 맨 뒤로 순번 교체
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CObject_UI* CUIMgr::GetTargetedUI(CObject_UI* _pParentUI)
{
	
	bool bLbtnAway = KEY_CHECK(LBTN, AWAY);

	// 1. 부모 UI 포함, 모든 자식들을 검사 한다.
	CObject_UI* pTargetUI = nullptr;

	static list<CObject_UI*> queue;
	static vector<CObject_UI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// 큐에서 데이터 하나 꺼내기
		CObject_UI* pUI= queue.front();
		queue.pop_front();
		
		// 큐에서 꺼내온 UI 가 TargetUI 인지 확인
		// 타겟 UI 둘 중, 더 우선순위가 높은 기준은 더 낮은 계층의 자식 UI
		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}

			pTargetUI = pUI;
		}
		else
		{
			// 왼쪽버튼 떼면, 눌렀던 체크를 다시 해제한다.
			vecNoneTarget.push_back(pUI);
		}

		const vector<CObject_UI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}
	
	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	return pTargetUI;
}
