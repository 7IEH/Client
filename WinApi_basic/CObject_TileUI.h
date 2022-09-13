#pragma once
#include "CObject_UI.h"

class CTexture;

class CObject_TileUI :
    public CObject_UI
{
public:


private:
    vec2                     m_vDragStart;
    CTexture*           m_pTex;

public:
    void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }


public:
    virtual void render(HDC _dc);
    
    virtual void MouseOn();


    CLONE(CObject_TileUI);

public:
    CObject_TileUI();
    ~CObject_TileUI();
};

