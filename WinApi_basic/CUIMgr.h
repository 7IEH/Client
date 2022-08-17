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

private:
	CObject_UI* GetFocusedUI();
	CObject_UI* GetTargetedUI(CObject_UI* _pParentUI);		// �θ� UI ������ ������ Ÿ���� �� UI �� ã�Ƽ� ��ȯ�Ѵ�.
};

