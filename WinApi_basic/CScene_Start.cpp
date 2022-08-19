#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CObject_Player.h"
#include "CObject_Monster.h"
#include "CObject_Background.h"

//#include "CTexture.h"
//#include "CPathMgr.h"
#include "CCollisionMgr.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
//#include"CEventMgr.h"
#include "CCamera.h"
#include"CCore.h"

CScene_Start::CScene_Start()
{

}

CScene_Start::~CScene_Start()
{

}

void CScene_Start::update()
{
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
	/*vector<CObject*> BackImage = vGetObject(GROUP_TYPE::BACK_IMAGE);
	vec2 CurPos = ((CObject_Background*)BackImage.front())->GetPos();
	CurPos = CurPos * fDT;
	BackImage.front()->SetPos(vec2(CurPos.x, 0.f));*/
}

void CScene_Start::Enter()
{
	// Object 추가
	CObject* pObj = new CObject_Player;
	
	pObj->SetName(L"Player");
	pObj->SetPos(vec2(640.f,640.f));
	pObj->SetScale(vec2(100.f,100.f));

	pushObject((UINT)GROUP_TYPE::PLAYER, pObj);

	CCamera::GetInst()->SetTarget(pObj);

	CObject_Monster* mObj = new CObject_Monster;

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

	pushObject((UINT)GROUP_TYPE::MONSTER, mObj);

	CObject* bObj = new CObject_Background;
	bObj->SetPos(vec2(0.f, 0.f));
	bObj->SetName(L"BACK_IMAGE");
	pushObject((UINT)GROUP_TYPE::BACK_IMAGE, bObj);


	// 충돌 지정
	// player 그룹과 Monster 그룹 간의 충돌 체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PLAYER);
	// stupid
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

	// Camera Look 지정
	vec2 vResolution = CCore::GetInst()->GetResolution();
	CCamera::GetInst()->SetLookAt(vResolution/2.f);
}



void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}