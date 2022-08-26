#include "pch.h"
#include "CScene_Title.h"

#include "CKeyMgr.h"
#include "CObject.h"
#include "CObject_UI.h"
#include "CObject_BtnUI.h"
#include "Background_Title.h"

#include "CCollisionMgr.h"
#include "CCore.h"

void StartScene(DWORD_PTR, DWORD_PTR);
void ToolScene(DWORD_PTR, DWORD_PTR);
void WindowExit(DWORD_PTR, DWORD_PTR);

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
	CObject* bObj = new Background_Title;
	bObj->SetPos(vec2(640.f, 384.f));
	pushObject((UINT)GROUP_TYPE::DEFAULT,bObj);

	CObject_BtnUI* BtnObj = new CObject_BtnUI;
	BtnObj->SetPos(vec2(940.f, 400.f));
	BtnObj->SetScale(vec2(300.f, 50.f));
	BtnObj->SetClickedCallBack(StartScene, 0, 0);
	pushObject((UINT)GROUP_TYPE::UI,BtnObj);

	CObject_BtnUI* BtnObj2 = new CObject_BtnUI;
	BtnObj2->SetPos(vec2(940.f, 490.f));
	BtnObj2->SetScale(vec2(300.f, 50.f));
	BtnObj2->SetClickedCallBack(ToolScene, 0, 0);
	pushObject((UINT)GROUP_TYPE::UI, BtnObj2);

	CObject_BtnUI* BtnObj3 = new CObject_BtnUI;
	BtnObj3->SetPos(vec2(940.f, 580.f));
	BtnObj3->SetScale(vec2(300.f, 50.f));
	BtnObj3->SetClickedCallBack(WindowExit, 0, 0);
	pushObject((UINT)GROUP_TYPE::UI, BtnObj3);
}

void CScene_Title::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}

void StartScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}

void ToolScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::TOOL);
}

void WindowExit(DWORD_PTR, DWORD_PTR)
{
	DestroyWindow(CCore::GetInst()->getHWND());
}
