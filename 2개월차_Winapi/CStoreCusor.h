#pragma once
#include "CUI.h"
class CStoreCusor :
    public CUI
{
    int       m_iItemNumber;
    int       m_iCount;
    CTexture* m_pTex;


    CTexture* m_pSoulball;
    CTexture* m_pFocus;
    Vec2 m_vDragStatrt;


public:
    virtual void update();
    virtual void render(HDC _dc);


public:

    CStoreCusor();
    ~CStoreCusor();

public:
    CLONE(CStoreCusor);

private:


};

