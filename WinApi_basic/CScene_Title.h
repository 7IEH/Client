#pragma once
#include "CScene.h"


class CScene_Title :
    public CScene
{
public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();
private:

public:
    CScene_Title();
    ~CScene_Title();
};

