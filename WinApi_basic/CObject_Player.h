#pragma once
#include "CObject.h"

class CTexture;

class CObject_Player :
    public CObject
{ 
public:
    virtual void update();
    virtual void render(HDC _dc);

    CLONE(CObject_Player)
private:
    void createMissile();

public:
    CObject_Player();
    CObject_Player(const CObject_Player& _origin)
        :CObject(_origin)
    {}
    ~CObject_Player();
};

