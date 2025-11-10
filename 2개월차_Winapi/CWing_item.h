#pragma once
#include "CUI.h"

class CTexuture;

class CWing_item : public CUI
{
    CTexture* m_pTex;

public:

    virtual void update();
    virtual void render(HDC _dc);

public:

    CWing_item();
    ~CWing_item();

public:
    CLONE(CWing_item);
};

