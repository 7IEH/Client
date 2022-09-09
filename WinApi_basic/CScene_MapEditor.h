#pragma once
#include "CScene.h"

class CScene_MapEditor :
    public CScene
{
public:
    virtual void Enter();
    virtual void update();
    virtual void Exit();

private:


public:
    CScene_MapEditor();
    ~CScene_MapEditor();
};

