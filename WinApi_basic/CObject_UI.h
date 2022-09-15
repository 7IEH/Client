#pragma once
#include "CObject.h"


class CObject_UI :
    public CObject
{
private:
    vector<CObject_UI*>            m_vecChildUI;
    CObject_UI*                            m_pParentUI;

    vec2                                          m_vFinalPos;
    
    bool                                           m_bCamAffected;                // UI 가 카메라에 영향을 받는 유무
    bool                                           m_bMouseOn;                        // UI 위에 마우스가 있는지
    bool                                           m_bLbtnDown;                      // UI 에 왼쪽버튼이 눌린적이 있는
    
    //PARENT
    UINT                                        m_ipSQNC;                               // 부모 UI 시퀸스 상태

    // BTN
    bool                                           m_bSQNC;                               // UI 시퀸스 유무
    UINT                                          m_iSQNC;                                // UI 시퀀스 넘버

public:
    vec2 GetFinalPos() { return m_vFinalPos; }
    CObject_UI* GetParent() { return m_pParentUI; }
    UINT GetSQNC() { return m_iSQNC; }
    UINT GetpSQNC() { return m_ipSQNC; }
    bool GetbSQNC() { return m_bSQNC; }
    bool IsMouseOn() { return m_bMouseOn; }
    bool IsLbtnDown() { return m_bLbtnDown; }

    void SetbSQNC(bool _bSQNC) { m_bSQNC = _bSQNC; }          // UI 시퀀스 넘버
    void SetSQNC(UINT _iSQNC) { m_iSQNC = _iSQNC; }               // UI 시퀸스 유무
    void SetpSQNC(UINT _ipSQNC) { m_ipSQNC = _ipSQNC; }      // 부모 UI 시퀸스 상태
    
    void AddChild(CObject_UI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }
    vector<CObject_UI*>& GetChildUI() { return m_vecChildUI; }

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

