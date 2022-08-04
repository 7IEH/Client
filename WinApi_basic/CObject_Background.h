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
   CLONE(CObject_Background)

public:
    CObject_Background();
    CObject_Background(const CObject_Background& _origin)
        :CObject(_origin)
        , m_pTex(_origin.m_pTex)
    {}    
    virtual ~CObject_Background();
};

