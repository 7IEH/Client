#pragma once
#include "CScene.h"

class CObject_UI;

class CScene_Tool :
    public CScene
{
private:
    CObject_UI* m_pUI;

public:
    virtual void Enter();
    virtual void Exit();
    virtual void update();

public:
    void SetTileIdx();

    void saveTileData();
    void SaveTile(const wstring& _strFilePath);

    void LoadTileData();

public:
    CScene_Tool ();
    ~CScene_Tool();

};

