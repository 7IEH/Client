#pragma once
#include "CObject.h"


class CObject_ScoreBox :
    public CObject
{
public:
    

private:
    bool    m_bSlide;

public:
    virtual void update();

    void SetSlide(bool _bSlide) { m_bSlide = _bSlide; }

    virtual void OnCollisionEnter(CCollider* _pOther);
    CLONE(CObject_ScoreBox)
public:
    CObject_ScoreBox();
    ~CObject_ScoreBox();

};

