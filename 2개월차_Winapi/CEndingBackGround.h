#pragma once
#include "CObject.h"
class CEndingBackGround :
    public CObject
{
    CTexture* m_pEndingTex;


public:
    virtual void update() override;
    virtual void render(HDC _dc) override;

public:
    CEndingBackGround();
    ~CEndingBackGround();
};

