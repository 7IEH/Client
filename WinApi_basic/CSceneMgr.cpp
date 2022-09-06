#include "pch.h"
#include "CSceneMgr.h"
#include "CCore.h"

#include "CScene_Title.h"
#include "CScene_Start.h"
//#include"CScene_Stage_01.h"
//#include "CScene_Stage_02.h"
#include "CScene_Loading.h"
#include "CScene_Tool.h"
#include "CEventMgr.h"

CSceneMgr::CSceneMgr() :m_arrScene{}, m_pCurScene(nullptr)
{

}

CSceneMgr::~CSceneMgr()
{
	// 씬 전부 삭제
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; i++) 
	{
		if(m_arrScene[i]!=nullptr)
			delete m_arrScene[i];
	}
}



void CSceneMgr::init()
{
	// scene 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");
	m_arrScene[(UINT)SCENE_TYPE::TITLE] = new CScene_Title;
	m_arrScene[(UINT)SCENE_TYPE::TITLE]->SetName(L"Title Scene");
	m_arrScene[(UINT)SCENE_TYPE::LOADING] = new CScene_Loading;
	m_arrScene[(UINT)SCENE_TYPE::LOADING]->SetName(L"Loading Scene");

	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage_01;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage_02;

	// 현재 씬 저장
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::TITLE];
	m_pCurScene->Enter();
}


void CSceneMgr::update()
{
	
	/*wchar_t szBuffer[255] = {};
	if (m_pCurScene->getName() == L"Start Scene")
	{
		swprintf_s(szBuffer, L"Start Scene");
		SetWindowText(CCore::GetInst()->getHWND(), szBuffer);
	}*/
	m_pCurScene->update();

	m_pCurScene->finalupdate();
};

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	m_pCurScene->Exit();

	m_pCurScene=m_arrScene[(UINT)_eNext];

	m_pCurScene->Enter();
}
