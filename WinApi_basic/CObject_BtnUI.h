#pragma once
#include "CObject_UI.h"

class CScene;
class CObject;
class CTexture;

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);
typedef void(*BTN_FUNC2) (wstring);

typedef void(CScene::* SCENE_MEMFUNC)(void);
typedef void(CObject::* OBJECT_MEMFUNC)(void);


class CObject_BtnUI :
    public CObject_UI
{
private:
    BTN_FUNC            m_pFunc;
    BTN_FUNC2            m_pFunc2;

    DWORD_PTR        m_param1;
    DWORD_PTR        m_param2;

    wstring                m_param3;


    CTexture*           m_pTex;


    SCENE_MEMFUNC m_pSceneFunc;
    CScene*                 m_pSceneInst;

    vec2                        m_vDragStart;

public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

    void SetClickedCallBack(BTN_FUNC _pFunc,DWORD_PTR _param1,DWORD_PTR _param2)
    {
        m_pFunc = _pFunc;
        m_param1 = _param1;
        m_param2 = _param2;
    }

    void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
    {
        m_pSceneInst = _pScene;
        m_pSceneFunc = _pSceneFunc;
    }

    void SetClickedCallBack(BTN_FUNC2 _pFunc, wstring _param3)
    {
        m_pFunc2 = _pFunc;
        m_param3 = _param3;
    }

    void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }

    virtual void render(HDC _dc);

public:
    CLONE(CObject_BtnUI);

public:
    CObject_BtnUI();
    ~CObject_BtnUI();
};

