#pragma once
#include "CUI.h"
class CHpBarUI :
    public CUI
{
private:

public:

    virtual void update();
    virtual void render(HDC _dc);

public:

    CHpBarUI();
    ~CHpBarUI();

public:
    CLONE(CHpBarUI);
};

