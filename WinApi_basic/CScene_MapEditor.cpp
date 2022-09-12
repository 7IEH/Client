#include "pch.h"
#include "CScene_MapEditor.h"
#include "CObject_PanelUI.h"
#include "CObject_BtnUI.h"
#include "CObject_TextUI.h"
#include "CCollisionMgr.h"

#include "CResMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"

#include "CTexture.h"

void RightPanel(DWORD_PTR, DWORD_PTR);
void LeftPanel(DWORD_PTR, DWORD_PTR);

CScene_MapEditor::CScene_MapEditor()
{
}

CScene_MapEditor::~CScene_MapEditor()
{
}

void CScene_MapEditor::update()
{
	CScene::update();
}

void CScene_MapEditor::Enter()
{
	CTexture* m_pTex = CResMgr::GetInst()->LoadTexture(L"Road_Tile", L"texture\\road_tile.bmp");

	CObject_PanelUI* pUI = new CObject_PanelUI;
	pUI->SetName(L"EditorPanel");
	pUI->SetPos(vec2(1160.f, 20.f));
	pUI->SetScale(vec2(232.f, 400.f));
	pUI->SetpSQNC(0);

	CObject_BtnUI* bUI = new CObject_BtnUI;
	bUI->SetPos(vec2(10.f, 10.f));
	bUI->SetScale(vec2(64.f, 64.f));
	bUI->SetSQNC(0);
	bUI->SetbSQNC(true);
	bUI->SetTexture(m_pTex);
	pUI->AddChild(bUI);

	bUI = new CObject_BtnUI;
	bUI->SetPos(vec2(10.f, 10.f));
	bUI->SetScale(vec2(64.f, 64.f));
	bUI->SetSQNC(1);
	bUI->SetbSQNC(true);
	pUI->AddChild(bUI);

	// 
	bUI = new CObject_BtnUI;
	bUI->SetPos(vec2(10.f, 340.f));
	bUI->SetScale(vec2(64.f, 20.f));
	bUI->SetClickedCallBack(LeftPanel, 0, 0);
	pUI->AddChild(bUI);

	// 
	bUI = new CObject_BtnUI;
	bUI->SetPos(vec2(158.f, 340.f));
	bUI->SetScale(vec2(64.f, 20.f));
	bUI->SetClickedCallBack(RightPanel, 0, 0);
	pUI->AddChild(bUI);

	// 
	CObject_TextUI* tUI = new CObject_TextUI;
	tUI->SetPos(vec2(84.f, 340.f));
	tUI->SetStr(L"패널1");
	tUI->SetSQNC(0);
	tUI->SetbSQNC(true);
	pUI->AddChild(tUI);

	tUI = new CObject_TextUI;
	tUI->SetPos(vec2(84.f, 340.f));
	tUI->SetStr(L"패널2");
	tUI->SetSQNC(1);
	tUI->SetbSQNC(true);
	pUI->AddChild(tUI);

	pushObject((UINT)GROUP_TYPE::UI, pUI);


}

void CScene_MapEditor::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}

void RightPanel(DWORD_PTR, DWORD_PTR)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*> UI = pCurScene->GetUIGroup();
	vector<CObject*>::iterator iter = UI.begin();

	for (; iter != UI.end(); ++iter)
	{
		if ((*iter)->GetName() == L"EditorPanel")
		{
			if (((CObject_UI*)(*iter))->GetpSQNC() < 1)
			{
				((CObject_UI*)(*iter))->SetpSQNC(((CObject_UI*)(*iter))->GetpSQNC() + 1);
			}
			else
			{
				((CObject_UI*)(*iter))->SetpSQNC(0);
			}
		}
	}
}

void LeftPanel(DWORD_PTR, DWORD_PTR)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*> UI = pCurScene->GetUIGroup();
	vector<CObject*>::iterator iter = UI.begin();

	for (; iter != UI.end(); ++iter)
	{
		if ((*iter)->GetName() == L"EditorPanel")
		{
			if (((CObject_UI*)(*iter))->GetpSQNC() > 0)
			{
				((CObject_UI*)(*iter))->SetpSQNC(((CObject_UI*)(*iter))->GetpSQNC() - 1);
			}
			else
			{
				((CObject_UI*)(*iter))->SetpSQNC(1);
			}
		}
	}
}