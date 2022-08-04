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

    int                     m_iHp;

public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

    void SetCenterPos(vec2 _vPos) { m_vCenterPos = _vPos; }

    void SetHp(const int _iHp) { m_iHp = _iHp; }
    const int GetHp() { return m_iHp; }

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    virtual void update();
    virtual void render(HDC _dc);

    CLONE(CObject_Monster)
private:
    void createMissile();


public:
    CObject_Monster();
    CObject_Monster(const CObject_Monster& _origin)
        :CObject(_origin)
        ,m_fSpeed(_origin.m_fSpeed)
        ,m_vCenterPos(_origin.m_vCenterPos)
        ,m_fMaxDistance(_origin.m_fMaxDistance)
        ,m_iDir(_origin.m_iDir)
        ,m_mTex(_origin.m_mTex)
        ,m_iHp(_origin.m_iHp)
    {}
    ~CObject_Monster();
};

