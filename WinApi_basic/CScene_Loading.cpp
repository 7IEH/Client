#include "pch.h"
#include "CScene_Loading.h"
#include "CObject_LoadingBar.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollisionMgr.h"

CScene_Loading::CScene_Loading()
{
}

CScene_Loading::~CScene_Loading()
{
}

void CScene_Loading::update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*> _object = pCurScene->vGetObject(GROUP_TYPE::DEFAULT);
	vector<CObject*>::iterator iter = _object.begin();

	for (; iter != _object.end(); ++iter)
	{
		if ((*iter)->GetName() == L"LOADINGBAR")
		{
			if (((CObject_LoadingBar*)(*iter))->Getprocess() == 5)
			{
				ChangeScene(SCENE_TYPE::START);
				return;
			}

			((CObject_LoadingBar*)(*iter))->Setprocess(((CObject_LoadingBar*)(*iter))->Getprocess() + 1);
			Sleep(1000);
		}
	}
}
// github commit

void CScene_Loading::Enter()
{
	CObject_LoadingBar* lbar = new CObject_LoadingBar;
	lbar->SetName(L"LOADINGBAR");
	lbar->SetPos(vec2(640.f, 500.f));
	pushObject(UINT(GROUP_TYPE::DEFAULT), lbar);
}

void CScene_Loading::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}