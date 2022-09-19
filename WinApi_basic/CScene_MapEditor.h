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
    void SaveMapData();
    void SaveMap(const wstring& _strFilePath);
   


public:
    CScene_MapEditor();
    ~CScene_MapEditor();
};

