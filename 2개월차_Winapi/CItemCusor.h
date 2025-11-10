#pragma once
#include "CUI.h"
class CItemCusor : public CUI
{

public:

    virtual void update();
    virtual void render(HDC _dc);

public:

    CItemCusor();
    ~CItemCusor();

public:
    CLONE(CItemCusor);
};

