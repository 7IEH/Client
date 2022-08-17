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

public:
    virtual void Save(FILE* _pFile);
    virtual void Load(FILE* _pFile);

    CLONE(CObject_Tile);
public:
    CObject_Tile();
    ~CObject_Tile();
};

