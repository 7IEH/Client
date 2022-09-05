#pragma once
#include "CObject.h"


class CObject_ScoreBox :
    public CObject
{
public:

private:

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    CObject_ScoreBox();
    ~CObject_ScoreBox();

};

