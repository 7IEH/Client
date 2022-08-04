#pragma once
#include "CObject.h"

class CTexture;

class CObject_Missile :
    public CObject
{
private:
    float            mi_fTheta; // 이동 방향
    float            mi_fSpeed;
    
    CTexture*   mi_miTex;  
 
public:
    virtual void update();
    virtual void render(HDC _dc);
    
    virtual void OnCollisionEnter(CCollider* _pOther);
 
    
public:
    void SetTheta(float _fTheta)
    {
        mi_fTheta = _fTheta;
    }

    CLONE(CObject_Missile)

public:
    CObject_Missile();
    CObject_Missile(const CObject_Missile& _origin)
        :CObject(_origin)
        ,mi_fTheta(_origin.mi_fTheta)
        ,mi_fSpeed(_origin.mi_fSpeed)
        ,mi_miTex(_origin.mi_miTex)
    {}
    ~CObject_Missile();
};

