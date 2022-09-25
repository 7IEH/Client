#include "pch.h"
#include "CScene_MapEditor.h"
#include "CObject_PanelUI.h"
#include "CObject_BtnUI.h"
#include "CObject_TextUI.h"
#include "CObject_TileUI.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CCore.h"


#include "CResMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCamera.h"

#include "CTexture.h"

void RightPanel(DWORD_PTR, DWORD_PTR);
void LeftPanel(DWORD_PTR, DWORD_PTR);
void TileCreated(wstring);

CScene_MapEditor::CScene_MapEditor()
{
}

CScene_MapEditor::~CScene_MapEditor()
{
}

void CScene_MapEditor::update()
{
	CScene::update();
	if (KEY_CHECK(ALT, TAP)) 
	{
		SaveMapData();
	}
}

void CScene_MapEditor::Enter()
{
	CCamera::GetInst()->SetLookAt(vec2(640.f, 384.f));

	CTexture* m_pTex = CResMgr::GetInst()->LoadTexture(L"Road_Tile", L"texture\\road_tile.bmp");

	CObject_PanelUI* pUI = new CObject_PanelUI;
	pUI->SetName(L"EditorPanel");
	pUI->SetPos(vec2(1160.f, 20.f));
	pUI->SetScale(vec2(232.f, 400.f));
	pUI->SetpSQNC(0);

	// 해당
	CObject_BtnUI* bUI = new CObject_BtnUI;
	bUI->SetPos(vec2(10.f, 10.f));
	bUI->SetScale(vec2(64.f, 64.f));
	bUI->SetSQNC(0);
	bUI->SetbSQNC(true);
	bUI->SetTexture(m_pTex);
	bUI->SetName(L"Road_Tile");
	bUI->SetClickedCallBack(TileCreated, L"Road_Tile");
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

// savemapdata position 개선 내일~
void CScene_MapEditor::SaveMapData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);						// 구조체 사이즈
	ofn.hwndOwner = CCore::GetInst()->getHWND();		// 윈도우 핸들 지정
	ofn.lpstrFile = szName;														// 경로	
	ofn.nMaxFile = sizeof(szName);											// 경로 이름 byte 수
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";					// 필터 들
	ofn.nFilterIndex = 0;															// 처음 열었을 때 filter 지정자
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"map";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetSaveFileName(&ofn))
	{
		SaveMap(szName);
	}
}

void CScene_MapEditor::SaveMap(const wstring& _strFilePath)
{
	wstring strFilePath = _strFilePath;

	// 커널 오브젝트
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");
	assert(pFile);

	const vector<CObject*>& vecMap = vGetObject(GROUP_TYPE::TILE);

	size_t size = vecMap.size();

	fwrite(&size, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < vecMap.size(); ++i)
	{
		fwrite(vecMap[i], sizeof(vecMap[i]), 1, pFile);
	}

	fclose(pFile);
}

void RightPanel(DWORD_PTR, DWORD_PTR)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& UI = pCurScene->GetUIGroup();
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

void TileCreated(wstring a)
{
	CTexture* m_pTex = CResMgr::GetInst()->LoadTexture(a, L"");
	CScene* CurScene = CSceneMgr::GetInst()->GetCurScene();



	CObject_TileUI* m_TUI = new CObject_TileUI;
	m_TUI->SetTexture(m_pTex);
	m_TUI->SetScale(vec2(64.f, 64.f));
	m_TUI->SetPos(RENDERPOS(MOUSE_POS));
	CurScene->pushObject((UINT)GROUP_TYPE::UI,m_TUI);
}