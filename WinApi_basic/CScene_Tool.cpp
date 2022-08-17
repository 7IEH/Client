#include "pch.h"
#include "CScene_Tool.h"

#include "CObject_Tile.h"
#include "CCore.h"
#include "CSceneMgr.h"
#include "CUIMgr.h"
#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "resource.h"
#include "CObject_PanelUI.h"
#include"CObject_BtnUI.h"

void changeScene(DWORD_PTR, DWORD_PTR);

CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Enter()
{
	// Ÿ�� ����
	CreateTile(5, 5);

	// UI ����
	CObject_UI* pPanelUI = new CObject_PanelUI;

	vec2 vResolution = CCore::GetInst()->GetResolution();
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(vec2(500.f, 300.f));
	pPanelUI->SetPos(vec2(vResolution.x- pPanelUI->GetScale().x,0.f));
	
	CObject_BtnUI* pBtnUI = new CObject_BtnUI;
	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetScale(vec2(100.f, 40.f));
	pBtnUI->SetPos(vec2(0.f,0.f));
	((CObject_BtnUI*)pBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Tool::saveTileData);
	pPanelUI->AddChild(pBtnUI);
	pushObject((UINT)GROUP_TYPE::UI, pPanelUI);

	CObject_UI* pClonePanel = pPanelUI->clone();
	pClonePanel->SetPos(vec2(vResolution.x - pPanelUI->GetScale().x, vResolution.y - pPanelUI->GetScale().y));
	((CObject_BtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(changeScene, 0, 0);
	pushObject((UINT)GROUP_TYPE::UI, pClonePanel);

	m_pUI = pClonePanel;

	// ī�޶�
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}

void CScene_Tool::Exit()
{
	DeleteAll();
}

void CScene_Tool::update()
{
	CScene::update();

	SetTileIdx();

	if (KEY_CHECK(LSHIFT, TAP))
	{

		// UI ��Ŀ�� ������ �ٲٱ�
		// CUIMgr::GetInst()->SetFocusedUI(m_pUI);
		saveTileData();
	}

	if (KEY_CHECK(CTRL, TAP))
	{

		// UI ��Ŀ�� ������ �ٲٱ�
		// CUIMgr::GetInst()->SetFocusedUI(m_pUI);

		LoadTileData();
	}
}

void CScene_Tool::SetTileIdx()
{
	if (KEY_CHECK(LBTN, TAP))
	{
		vec2 vMousePos = MOUSE_POS;
		vMousePos =	CCamera::GetInst()->GetRealPos(vMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iCol = (int)(vMousePos.x / 60);
		int iRow = (int)(vMousePos.y / 80);

		if ( vMousePos.x < 0.f || iTileX <= iCol 
			|| vMousePos.y < 0.f || iTileY <= iRow )
		{
			return;
		}

		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObject*>& vecTile=vGetObject(GROUP_TYPE::TILE); 
		((CObject_Tile*)vecTile[iIdx])->AddImgIdx();
	}
}

void CScene_Tool::saveTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);						// ����ü ������
	ofn.hwndOwner = CCore::GetInst()->getHWND();		// ������ �ڵ� ����
	ofn.lpstrFile = szName;														// ���	
	ofn.nMaxFile = sizeof(szName);											// ��� �̸� byte ��
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";					// ���� ��
	ofn.nFilterIndex = 0;															// ó�� ������ �� filter ������
	ofn.lpstrFileTitle = nullptr;													
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
	wstring strFilePath = _strFilePath;

	// Ŀ�� ������Ʈ
	FILE* pFile = nullptr;

	_wfopen_s(&pFile,strFilePath.c_str(),L"wb");
	// ���� ���� ����
	assert(pFile);

	// ������ ����
	// Ÿ�� ���μ��� ���� ����
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	// Ÿ�ϵ��� ���������� ������ �����͸� �����ϰ� ��
	const vector<CObject*>& vecTile = vGetObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CObject_Tile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}

void CScene_Tool::LoadTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);						// ����ü ������
	ofn.hwndOwner = CCore::GetInst()->getHWND();		// ������ �ڵ� ����
	ofn.lpstrFile = szName;														// ���	
	ofn.nMaxFile = sizeof(szName);											// ��� �̸� byte ��
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";					// ���� ��
	ofn.nFilterIndex = 0;															// ó�� ������ �� filter ������
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetOpenFileName(&ofn))
	{
		LoadTile(CPathMgr::GetInst()->GetRelativePath(szName));
	}
}



void changeScene(DWORD_PTR , DWORD_PTR )
{
	ChangeScene(SCENE_TYPE::START);
}





// =========================
// Tile Count Window Proc
// =========================

INT_PTR __stdcall TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);	
			
			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if(LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
