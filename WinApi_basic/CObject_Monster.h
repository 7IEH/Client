#pragma once
#include "CObject.h"

class CTexture;

class CObject_Monster :
    public CObject
{

private:
    vec2                 m_vCenterPos;
    float                m_fSpeed;
    float                m_fMaxDistance;
    int                     m_iDir;
    CTexture*       m_mTex;

public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

    void SetCenterPos(vec2 _vPos) { m_vCenterPos = _vPos; }

public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void createMissile();

public:
    CObject_Monster();
    ~CObject_Monster();
};

