#pragma once
#include "CObject.h"

class CTexture;

class CObject_Missile :
    public CObject
{
private:
    float            mi_fTheta; // 이동 방향
    float            mi_fSpeed;
    
    vec2             mi_vDir;

    CTexture*   mi_miTex;
 
public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    void SetTheta(float _fTheta)
    {
        mi_fTheta = _fTheta;
    }

public:
    CObject_Missile();
    ~CObject_Missile();
};

