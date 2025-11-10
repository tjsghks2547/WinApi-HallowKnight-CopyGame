#pragma once
#include "CObject.h"

class CTexture;

class CStartBackGround :
    public CObject
{
private:
    CTexture* m_pTex;
    CTexture* m_pCusorTex;


public:
    virtual void update() override;
    virtual void render(HDC _dc) override;

public:
    CStartBackGround();
    ~CStartBackGround();
};

