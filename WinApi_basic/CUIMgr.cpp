#include "pch.h"
#include "CUIMgr.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject_UI.h"

CUIMgr::CUIMgr()
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->vGetObject(GROUP_TYPE::UI);


	bool bLbtnTap = KEY_CHECK(LBTN, TAP);
	bool bLbtnAway = KEY_CHECK(LBTN, AWAY);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CObject_UI* pUI = (CObject_UI*)vecUI[i];
		if (pUI->IsMouseOn())
		{
			pUI->MouseOn();

			if (bLbtnTap)
			{
				pUI->MouseLbtnDown();
				pUI->m_bLbtnDown = true;
			}
			else if(bLbtnAway)
			{
				pUI->MouseLbtnUp();

				if (pUI->m_bLbtnDown)
				{
					pUI->MouseLbtnClicked();
				}
				pUI->m_bLbtnDown = false;
			}
		}
		else
		{
			if (bLbtnAway)
			{
				pUI->m_bLbtnDown = false;
			}
		}
		
	}

}
