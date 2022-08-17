#pragma once
#include "CObject_UI.h"


class CObject_PanelUI :
    public CObject_UI
{
private:
    vec2              m_vDragStart;

public:
    virtual void update();

    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();

public:
    CLONE(CObject_PanelUI);

public:
    CObject_PanelUI();
    ~CObject_PanelUI();
};

