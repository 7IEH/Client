#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CObject_Player.h"
#include "CObject_Monster.h"
#include "CObject_Background.h"
#include "CObject_UI.h"
#include "CObject_PanelUI.h"
#include "CObject_BtnUI.h"
#include "CObject_TextUI.h"
#include "CObject_Tile.h"
#include "CObject_ScoreBox.h"

#include "CTexture.h"
//#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CCollider.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
//#include"CEventMgr.h"
#include "CCamera.h"
#include "CSceneMgr.h"
#include"CCore.h"


void MenuReturn(DWORD_PTR, DWORD_PTR);
void ReStart(DWORD_PTR, DWORD_PTR);

CScene_Start::CScene_Start()
	:m_iScore(0)
{

}

CScene_Start::~CScene_Start()
{

}

void CScene_Start::update()
{
	ScoreCaculate();
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vUI = pCurScene->GetUIGroup();
	vector<CObject*>::iterator iter = vUI.begin();
	for (; iter != vUI.end(); ++iter)
	{
		if ((*iter)->GetName() == L"Score_Text")
		{
			((CObject_TextUI*)(*iter))->SetStr(std::to_wstring(m_iScore).c_str());
		}
		if ((*iter)->GetName() == L"Score_Text")
		{
			((CObject_TextUI*)(*iter))->SetStr(std::to_wstring(m_iScore).c_str());
		}
	}


	CScene::update();
	if (KEY_CHECK(ENTER, TAP))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_CHECK(LBTN, TAP))
	{
		vec2 vLookAt=CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}
}

void CScene_Start::Enter()
{
	// player_object 추가
	CObject* pObj = new CObject_Player;
	
	pObj->SetName(L"Player");
	pObj->SetPos(vec2(240.f,640.f));
	pObj->SetScale(vec2(100.f,100.f));

	pushObject((UINT)GROUP_TYPE::PLAYER, pObj);

	//CCamera::GetInst()->SetTarget(pObj);

	/*CObject_Monster* mObj = new CObject_Monster;

	mObj->SetName(L"Monster");
	mObj->SetPos(vec2(200.f, 200.f));
	mObj->SetScale(vec2(50, 50));
	mObj->SetCenterPos(vec2(200.f, 200.f));
	mObj->SetHp(100);

	pushObject((UINT)GROUP_TYPE::MONSTER, mObj);

	mObj = new CObject_Monster;

	mObj->SetName(L"Monster");
	mObj->SetPos(vec2(500.f, 200.f));
	mObj->SetScale(vec2(50, 50));
	mObj->SetCenterPos(vec2(500.f, 200.f));
	mObj->SetHp(100);

	pushObject((UINT)GROUP_TYPE::MONSTER, mObj);*/

	vec2 vResolution = CCore::GetInst()->GetResolution();

	CObject* bObj = new CObject_Background;
	bObj->SetPos(vec2(640.f, 384.f));
	bObj->SetName(L"BACK_IMAGE");
	pushObject((UINT)GROUP_TYPE::BACK_IMAGE, bObj);

	CObject* bObj2 = new CObject_Background;
	bObj2->SetPos(vec2(1920.f, 384.f));
	bObj2->SetName(L"BACK_IMAGE2");
	pushObject((UINT)GROUP_TYPE::BACK_IMAGE, bObj2);

	/*CObject_UI* PanelUI = new CObject_PanelUI;
	PanelUI->SetPos(vec2(vResolution.x - 400.f, 50.f));
	PanelUI->SetScale(vec2(390.f, 500.f));

	CObject_BtnUI* BtnUI = new CObject_BtnUI;
	BtnUI->SetPos(vec2(0.f,0.f));
	BtnUI->SetScale(vec2(100.f, 100.f));
	BtnUI->SetTexture(m_pTex);
	BtnUI->SetName(L"childbutton");
	PanelUI->AddChild(BtnUI);
	pushObject((UINT)GROUP_TYPE::UI, PanelUI);*/
	CTexture* m_pTex = CResMgr::GetInst()->LoadTexture(L"TILE", L"texture\\road_tile.bmp");
	
	CObject_TextUI* textObj = new CObject_TextUI;
	textObj->SetPos(vec2(100.f, 100.f));
	textObj->SetStr(std::to_wstring(m_iScore).c_str());
	textObj->SetName(L"Score_Text");
	pushObject((UINT)GROUP_TYPE::UI, textObj);
	
	for (size_t i = 0; i < 20; ++i)
	{
		CObject_Tile* pTile = new CObject_Tile;
		pTile->SetPos(vec2((i*64.f)+32.f, 736.f));
		pTile->SetName(L"FLOOR");
		pTile->SetTexture(m_pTex);
		pTile->CreateCollider();
		pTile->GetCollider()->SetScale(vec2(64.f, 64.f));
		pushObject((UINT)GROUP_TYPE::TILE, pTile);
	}

	CObject_Tile* pTile = new CObject_Tile;
	pTile->SetPos(vec2(992.f,672.f));
	pTile->SetName(L"OBSTACLE");
	pTile->SetTexture(m_pTex);
	pTile->CreateCollider();
	pTile->GetCollider()->SetScale(vec2(40.f, 40.f));
	/*pTile->SetSlide(true);*/
	pushObject((UINT)GROUP_TYPE::TILE, pTile);
	
	CObject_ScoreBox* pSB = new CObject_ScoreBox;
	pSB->SetPos(vec2(992.f, 572.f));
	pSB->SetName(L"SCORE_BOX");
	pSB->SetSlide(true);
	pushObject((UINT)GROUP_TYPE::SCORE_BOX, pSB);

	// 충돌 지정
	// player 그룹과 Monster 그룹 간의 충돌 체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PLAYER);
	// stupid
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	// player 그룹과 Tile 그룹 간의 충돌 체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::TILE);
	// player 그룹과 ScoreBox 그룹 간의 충돌 체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::SCORE_BOX);

	// Camera Look 지정
	CCamera::GetInst()->SetLookAt(vResolution/2.f);
}



void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}

void CScene_Start::DiePanel()
{
	CObject_PanelUI* _pUI = new CObject_PanelUI;
	_pUI->SetPos(vec2(300.f, 384.f));
	_pUI->SetScale(vec2(700.f, 400.f));
	
	CObject_TextUI* _tUI = new CObject_TextUI;
	_tUI->SetStr(L"다시 시작하시겠습니까?");
	_tUI->SetPos(vec2(350.f, 100.f));
	_pUI->AddChild(_tUI);

	CObject_BtnUI* _bUI = new CObject_BtnUI;
	_bUI->SetPos(vec2(175.f, 200.f));
	_bUI->SetScale(vec2(150.f, 50.f));
	_bUI->SetClickedCallBack(ReStart,0,0);
	_pUI->AddChild(_bUI);

	_bUI = new CObject_BtnUI;
	_bUI->SetPos(vec2(525.f, 200.f));
	_bUI->SetScale(vec2(150.f, 50.f));
	_bUI->SetClickedCallBack(MenuReturn, 0, 0);
	_pUI->AddChild(_bUI);


	pushObject((UINT)GROUP_TYPE::UI,_pUI);
}

void MenuReturn(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::TITLE);
}

void ReStart(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}