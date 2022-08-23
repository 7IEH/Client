#pragma once
#include "CObject.h"

class CTexture;

class CObject_Player :
    public CObject
{ 
private:
    bool			m_IsJump;
        
public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    void SetIsJump(bool _b) { m_IsJump = _b; }

    bool GetIsJump() { return m_IsJump; }

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

