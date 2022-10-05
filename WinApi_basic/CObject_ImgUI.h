#pragma once
#include "CObject_UI.h"

class CTexture;

class CObject_ImgUI :
    public CObject_UI
{
private:
    CTexture* m_pTex;
    vec2 m_vLT;                                    // 해당 img LT
    vec2 m_vRB;                                   // 해당 img RB

public:
    virtual void render(HDC _dc);

    void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }

    void SetLT(vec2 _vLT) { m_vLT = _vLT; }
    void SetRB(vec2 _vRB) { m_vRB = _vRB; }

    vec2 GetLT() { return m_vLT; }
    vec2 GetRB() { return m_vRB; }

    CLONE(CObject_ImgUI);
public:
    CObject_ImgUI();
    ~CObject_ImgUI();
};

