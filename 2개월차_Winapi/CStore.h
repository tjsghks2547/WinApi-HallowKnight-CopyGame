#pragma once
#include "CUI.h"
class CStore :
    public CUI
{
private:

    CTexture* m_pTex;
    
    int m_iCount;

public:

    virtual void update();
    virtual void render(HDC _dc);

public:

    CStore();
    ~CStore();

public:
    CLONE(CStore);

private:
};

