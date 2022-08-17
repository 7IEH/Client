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
	// 1. FocusedUI Ȯ��
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
		return;

	// 2. FocusedUI ������, �θ� UI ����, �ڽ� UI �� �� ���� Ÿ���� �� UI �� �����´�.
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

			// ���ʹ�ư ����, ������ üũ�� �ٽ� �����Ѵ�.
			pTargetUI->m_bLbtnDown = false;
		}
	}
}

void CUIMgr::SetFocusedUI(CObject_UI* _pUI)
{
	// �̹� ��Ŀ�� ���� ��� or ��Ŀ�� ������û�� ���
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

	// ���� ������ �� �ڷ� ���� ��ü
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}

CObject_UI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_CHECK(LBTN, TAP);

	// ���� ��Ŀ�� UI�� �޾Ƶΰ� ����Ǿ����� Ȯ���Ѵ�.
	CObject_UI* pFocusedUI = m_pFocusedUI;

	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	// ���ʹ�ư TAP �� �߻��� ��Ȳ
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter < vecUI.end(); ++iter)
	{
		if (((CObject_UI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}
	
	// �̹��� Focus �� UI�� ����.
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusedUI = (CObject_UI*)*targetiter;

	// ���� ������ �� �ڷ� ���� ��ü
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CObject_UI* CUIMgr::GetTargetedUI(CObject_UI* _pParentUI)
{
	
	bool bLbtnAway = KEY_CHECK(LBTN, AWAY);

	// 1. �θ� UI ����, ��� �ڽĵ��� �˻� �Ѵ�.
	CObject_UI* pTargetUI = nullptr;

	static list<CObject_UI*> queue;
	static vector<CObject_UI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// ť���� ������ �ϳ� ������
		CObject_UI* pUI= queue.front();
		queue.pop_front();
		
		// ť���� ������ UI �� TargetUI ���� Ȯ��
		// Ÿ�� UI �� ��, �� �켱������ ���� ������ �� ���� ������ �ڽ� UI
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
			// ���ʹ�ư ����, ������ üũ�� �ٽ� �����Ѵ�.
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
