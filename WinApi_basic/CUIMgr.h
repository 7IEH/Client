#pragma once


class CObject_UI;

class CUIMgr
{
public:
	SINGLE(CUIMgr);

private:
	CObject_UI*                 m_pFocusedUI;

public:
	void update();

	void SetFocusedUI(CObject_UI* _pUI);
	CObject_UI* GetFocusedUI();

private:
	CObject_UI* GetTargetedUI(CObject_UI* _pParentUI);		// 부모 UI 내에서 실제로 타겟팅 된 UI 를 찾아서 반환한다.
};

