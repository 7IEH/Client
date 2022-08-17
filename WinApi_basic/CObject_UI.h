#pragma once
#include "CObject.h"


class CObject_UI :
    public CObject
{
private:
    vector<CObject_UI*>            m_vecChildUI;
    CObject_UI*                            m_pParentUI;

    vec2                                          m_vFinalPos;
    
    bool                                           m_bCamAffected;        // UI �� ī�޶� ������ �޴� ����
    bool                                           m_bMouseOn;                // UI ���� ���콺�� �ִ���
    bool                                           m_bLbtnDown;              // UI �� ���ʹ�ư�� �������� �ִ�

public:
    vec2 GetFinalPos() { return m_vFinalPos; }
    CObject_UI* GetParent() { return m_pParentUI; }
    bool IsMouseOn() { return m_bMouseOn; }
    bool IsLbtnDown() { return m_bLbtnDown; }

    void AddChild(CObject_UI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }
    const vector<CObject_UI*>& GetChildUI() { return m_vecChildUI; }

public:
    virtual void update();
    virtual void finalupdate();
    virtual void render(HDC _DC);


public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();
    /*virtual void MouseRbtnDown();
    virtual void MouseRbtnUp();*/

private:
    void update_child();
    void finalupdate_child();
    void render_child(HDC _dc);

    void MouseOnCheck();

public:
    virtual CObject_UI* clone() = 0;

public:
    CObject_UI(bool _bCamAff);
    CObject_UI(const CObject_UI& _origin);
    virtual ~CObject_UI();

    friend class CUIMgr;
};

