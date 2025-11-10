#pragma once
#include "CUI.h"

class CBlackFilter :
    public CUI
{
private:


public:

    virtual void update();
    virtual void render(HDC _dc);

public:

    CBlackFilter();
    ~CBlackFilter();

public:
    CLONE(CBlackFilter);
};

