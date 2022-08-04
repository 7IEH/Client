#pragma once
#include "CObject.h"

class CTexture;

class Background_Title :
    public CObject
{
private:
    CTexture* m_pTex;

public:
    virtual void render(HDC _dc);

    CLONE(Background_Title)

public:
    Background_Title();
    Background_Title(const Background_Title& _origin)
        :CObject(_origin)
        , m_pTex(_origin.m_pTex)
    {}
    virtual ~Background_Title();

};

