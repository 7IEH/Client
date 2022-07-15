#pragma once
#include "CObject.h"

class CTexture;

class CObject_Background :
    public CObject
{
private:
    CTexture* m_pTex;

public:
    virtual void render(HDC _dc);

public:
    CObject_Background();
    ~CObject_Background();
};

