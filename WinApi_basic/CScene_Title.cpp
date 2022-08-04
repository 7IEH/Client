#include "pch.h"
#include "CScene_Title.h"

#include "CKeyMgr.h"
#include "CObject.h"
#include "Background_Title.h"

#include "CCollisionMgr.h"

CScene_Title::CScene_Title()
{
}

CScene_Title::~CScene_Title()
{
}

void CScene_Title::update()
{
	CScene::update();
	if (KEY_CHECK(ENTER, TAP)) 
	{
		ChangeScene(SCENE_TYPE::START);
	}
}

void CScene_Title::Enter()
{
	CObject* bObj = new Background_Title;
	bObj->SetPos(vec2(640.f, 384.f));
	pushObject((UINT)GROUP_TYPE::DEFAULT,bObj);
}

void CScene_Title::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}


