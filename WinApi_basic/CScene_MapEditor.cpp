#include "pch.h"
#include "CScene_MapEditor.h"
#include "CObject_PanelUI.h"
#include "CObject_BtnUI.h"
#include "CObject_TextUI.h"
#include "CCollisionMgr.h"

CScene_MapEditor::CScene_MapEditor()
{
}

CScene_MapEditor::~CScene_MapEditor()
{
}

void CScene_MapEditor::update()
{

}

void CScene_MapEditor::Enter()
{
	CObject_PanelUI* pUI = new CObject_PanelUI;
	pUI->SetPos(vec2(1160.f, 20.f));
	pUI->SetScale(vec2(232.f, 400.f));

	CObject_BtnUI* bUI = new CObject_BtnUI;
	bUI->SetPos(vec2(10.f, 10.f));
	bUI->SetScale(vec2(64.f, 64.f));
	pUI->AddChild(bUI);

	bUI = new CObject_BtnUI;
	bUI->SetPos(vec2(10.f, 340.f));
	bUI->SetScale(vec2(64.f, 20.f));
	pUI->AddChild(bUI);

	bUI = new CObject_BtnUI;
	bUI->SetPos(vec2(158.f, 340.f));
	bUI->SetScale(vec2(64.f, 20.f));
	pUI->AddChild(bUI);

	CObject_TextUI* tUI = new CObject_TextUI;
	tUI->SetPos(vec2(84.f, 340.f));
	tUI->SetStr(L"ÆĞ³Î");
	pUI->AddChild(tUI);

	pushObject((UINT)GROUP_TYPE::UI, pUI);


}

void CScene_MapEditor::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}