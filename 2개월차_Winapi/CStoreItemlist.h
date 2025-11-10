#pragma once
#include "CUI.h"
class CStoreItemlist :
    public CUI
{
    int       m_iItemNumber;
    int       m_iCount;
    CTexture* m_pSoulBallTex;
    CTexture* m_pFocusTex;
    
    Vec2 m_vDragStatrt;


public:
    virtual void update();
    virtual void render(HDC _dc);


public:

    CStoreItemlist();
    ~CStoreItemlist();

public:
    CLONE(CStoreItemlist);

};

