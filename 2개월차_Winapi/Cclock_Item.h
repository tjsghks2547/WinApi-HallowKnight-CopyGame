#pragma once
#include "CUI.h"

class CTexture;


class Cclock_Item : public CUI
{
    CTexture* m_pTex;

public:

    virtual void update();
    virtual void render(HDC _dc);

public:

    Cclock_Item();
    ~Cclock_Item();

public:
    CLONE(Cclock_Item);
};

