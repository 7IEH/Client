#pragma once
#include "CObject_UI.h"
class CObject_TextUI :
    public CObject_UI
{
public:
    virtual void update();
    virtual void render(HDC _dc);

private:
   wstring m_Str;


public:
    void SetStr(wstring _Str) { m_Str = _Str; }
    wstring GetStr() { return m_Str; }


    CLONE(CObject_TextUI);

public:
    CObject_TextUI();
    ~CObject_TextUI();
};

