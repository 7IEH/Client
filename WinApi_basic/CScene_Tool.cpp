#include "pch.h"
#include "CScene_Tool.h"

#include "CObject_Tile.h"
#include "CCore.h"
#include "CSceneMgr.h"

#include "CResMgr.h"
#include "CKeyMgr.h"
#include "resource.h"
#include "CObject_UI.h"

CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Enter()
{

	// 鸥老 积己
	CreateTile(5, 5);

	// UI 积己
	CObject_UI* pUI = new CObject_UI(false);

	vec2 vResolution = CCore::GetInst()->GetResolution();
	pUI->SetScale(vec2(500.f, 300.f));
	pUI->SetPos(vec2(vResolution.x-pUI->GetScale().x,0.f));
	
	/*CObject_UI* pChildUI = new CObject_UI;
	pChildUI->SetScale(vec2(100.f, 40.f));
	pChildUI->SetPos(vec2(0.f,0.f));

	pUI->AddChild(pChildUI);*/

	pushObject((UINT)GROUP_TYPE::UI, pUI);

	// 墨皋扼
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}

void CScene_Tool::Exit()
{
}

void CScene_Tool::update()
{
	CScene::update();

	SetTileIdx();
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
