#pragma once
#include "CObject.h"

class CTexture;

class CObject_Player :
    public CObject
{
private:
    CTexture *m_pTex;
    
public:
    virtual void update();
    virtual void render(HDC _dc);


private:
    void createMissile();


public:
    CObject_Player();
    ~CObject_Player();
};

