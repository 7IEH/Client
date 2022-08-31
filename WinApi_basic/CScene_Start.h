#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{
public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

private:
    UINT m_iScore;

public:
    void SetScore(UINT _iScore) { m_iScore = _iScore; }
    UINT GetScore() { return m_iScore; }

public:
    CScene_Start();
    ~CScene_Start();
};

