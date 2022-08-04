#pragma once
#include "CObject.h"


class CTexture;

class CObject_Tile :
    public CObject
{
private:
    CTexture*           m_pTileTex;
    int                         m_iImgIdx;

public:
    void SetTexture(CTexture* _pTex)
    {
        m_pTileTex = _pTex;
    }

    void AddImgIdx()
    {
        ++m_iImgIdx;
    }

private:
    virtual void update();
    virtual void render(HDC _dc);


    CLONE(CObject_Tile);
public:
    CObject_Tile();
    ~CObject_Tile();
};

