#pragma once
#include "CUI.h"



class CLiquidUI :
    public CUI
{
private:

public:
    
 

    virtual void update();
    virtual void render(HDC _dc);

public:

    CLiquidUI();
    ~CLiquidUI();

public:
    CLONE(CLiquidUI);

private: 
    int  m_iLiquid_amount;
   
};

