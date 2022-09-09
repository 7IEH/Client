#include "pch.h"
#include "CScene_Title.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CTexture.h"
#include "CObject.h"
#include "CObject_UI.h"
#include "CObject_BtnUI.h"
#include "Background_Title.h"

#include "CCollisionMgr.h"
#include "CCore.h"

void StartScene(DWORD_PTR, DWORD_PTR);
void ToolScene(DWORD_PTR, DWORD_PTR);
void WindowExit(DWORD_PTR, DWORD_PTR);
void EditorScene(DWORD_PTR, DWORD_PTR);

CScene_Title::CScene_Title()
{
}

CScene_Title::~CScene_Title()
{
}

void CScene_Title::update()
{
	CScene::update();
	//if (KEY_CHECK(ENTER, TAP)) 
	//{
	//	//ChangeScene(SCENE_TYPE::START);
	//}
}

void CScene_Title::Enter()
{
	/*CObject* bObj = new Background_Title;
	bObj->SetPos(vec2(640.f, 384.f));
	pushObject((UINT)GROUP_TYPE::DEFAULT,bObj);*/


	CTexture* _start_tex = CResMgr::GetInst()->LoadTexture(L"startbutton", L"texture\\startbutton.bmp");
	CTexture* _tool_tex = CResMgr::GetInst()->LoadTexture(L"toolbutton", L"texture\\toolbutton.bmp");
	CTexture* _editor_tex= CResMgr::GetInst()->LoadTexture(L"editorbutton", L"texture\\editorbutton.bmp");
	CTexture* _exit_tex = CResMgr::GetInst()->LoadTexture(L"exitbutton", L"texture\\exitbutton.bmp");

	// button texture bitblt 좀 더 알아보기
	CObject_BtnUI* BtnObj = new CObject_BtnUI;
	BtnObj->SetPos(vec2(940.f, 400.f));
	BtnObj->SetScale(vec2(300.f, 50.f));
	BtnObj->SetClickedCallBack(StartScene, 0, 0);
	BtnObj->SetTexture(_start_tex);
	BtnObj->SetName(L"Start_button");
	pushObject((UINT)GROUP_TYPE::UI,BtnObj);

	BtnObj = new CObject_BtnUI;
	BtnObj->SetPos(vec2(940.f, 490.f));
	BtnObj->SetScale(vec2(300.f, 50.f));	
	BtnObj->SetClickedCallBack(EditorScene, 0, 0);
	BtnObj->SetTexture(_editor_tex);
	BtnObj->SetName(L"Editor_button");
	pushObject((UINT)GROUP_TYPE::UI, BtnObj);

    BtnObj = new CObject_BtnUI;
	BtnObj->SetPos(vec2(940.f, 580.f));
	BtnObj->SetScale(vec2(300.f, 50.f));
	BtnObj->SetClickedCallBack(WindowExit, 0, 0);
	BtnObj->SetTexture(_exit_tex);
	BtnObj->SetName(L"Exit_button");
	pushObject((UINT)GROUP_TYPE::UI, BtnObj);
}

void CScene_Title::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}

void StartScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::LOADING);
}

void ToolScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::TOOL);
}

void EditorScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::EDITOR);
}

void WindowExit(DWORD_PTR, DWORD_PTR)
{
	DestroyWindow(CCore::GetInst()->getHWND());
}
