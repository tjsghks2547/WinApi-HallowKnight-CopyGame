#pragma once
#include "CUI.h"
class CGeo : public CUI
{
private:

public:

    virtual void update();
    virtual void render(HDC _dc);

public:

    CGeo();
    ~CGeo();

public:
    CLONE(CGeo);
};

