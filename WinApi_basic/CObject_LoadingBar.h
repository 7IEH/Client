#pragma once
#include "CObject.h"

class CTextue;

class CObject_LoadingBar :
    public CObject
{
public:
    CTexture* m_pTex;
    int m_iprocess;
private:
   
public:
    virtual void render(HDC _dc);

public:
    int Getprocess() { return m_iprocess; }

    void Setprocess(int _iprocess) { m_iprocess = _iprocess; }

    CLONE(CObject_LoadingBar)
public:
    CObject_LoadingBar();
    ~CObject_LoadingBar();
};

