#pragma once
#include "CScene.h"


class CScene_Loading :
    public CScene
{
public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();
private:

public:
    CScene_Loading();
    ~CScene_Loading();
};

