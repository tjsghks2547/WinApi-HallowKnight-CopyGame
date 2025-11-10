#pragma once
#include "CUI.h"

class CTexuture;

class CInventory :
    public CUI
{
private:

    int       m_iItemNumber;
    int       m_iCount;
    CTexture* m_pTex;
    Vec2 m_vDragStatrt;


public:
    virtual void update();
    virtual void render(HDC _dc);


    virtual void MouseOn(); // ui에 마우스 위가 올라올때
    virtual void MouseLbtnDown(); // ui를 마우스 버튼으로 눌렀을때
    virtual void MouseLbtnUp(); // 마우스 누름이 떼졌을 때 

public:

    CInventory();
    ~CInventory();

public:
    CLONE(CInventory);

private:
  

};

