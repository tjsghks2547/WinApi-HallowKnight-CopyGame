#pragma once
#include "CUI.h"
class CHUD :
    public CUI
{
public:

    virtual void update();
    virtual void render(HDC _dc);

public:

    CHUD();
    ~CHUD();

    CLONE(CHUD);
};

