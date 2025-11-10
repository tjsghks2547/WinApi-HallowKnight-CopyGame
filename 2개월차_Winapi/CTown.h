#pragma once
#include "CObject.h"
class CTown :
    public CObject
{
private:
    CTexture* m_pTex;
    Vec2  vPos;

public:
    virtual void update() override;
    virtual void render(HDC _dc) override;

public:
    CTown();
    ~CTown();
};

