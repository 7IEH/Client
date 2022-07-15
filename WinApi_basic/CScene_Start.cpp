#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CObject_Player.h"
#include "CObject_Monster.h"
#include "CObject_Background.h"

#include "CTexture.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"

CScene_Start::CScene_Start()
{

}

CScene_Start::~CScene_Start()
{

}

void CScene_Start::Enter()
{
	// Object 추가
	CObject* pObj = new CObject_Player;

	pObj->SetPos(vec2(640.f,640.f));
	pObj->SetScale(vec2(100.f,100.f));

	pushObject((UINT)GROUP_TYPE::PLAYER, pObj);

	CObject_Monster* mObj = new CObject_Monster;

	mObj->SetPos(vec2(200.f, 200.f));
	mObj->SetScale(vec2(50, 50));
	mObj->SetCenterPos(vec2(200.f, 200.f));

	pushObject((UINT)GROUP_TYPE::MONSTER, mObj);

	mObj = new CObject_Monster;

	mObj->SetPos(vec2(500.f, 200.f));
	mObj->SetScale(vec2(50, 50));
	mObj->SetCenterPos(vec2(500.f, 200.f));

	pushObject((UINT)GROUP_TYPE::MONSTER, mObj);

	CObject* bObj = new CObject_Background;
	mObj->SetPos(vec2(640.f, 384.f));
	pushObject((UINT)GROUP_TYPE::DEFAULT, bObj);

	// 충돌 지정
	// player 그룹과 Monster 그룹 간의 충돌 체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);

}



void CScene_Start::Exit()
{
	CCollisionMgr::GetInst()->Reset();
}