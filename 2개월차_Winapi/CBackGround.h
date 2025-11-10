#pragma once
#include "CObject.h"


class CTexture; 

class CBackGround : public CObject
{

private:
    CTexture* m_pTex; 
    Vec2  vPos;

public:
    virtual void update() override;
    virtual void render(HDC _dc) override;

public:
    CBackGround();
    ~CBackGround();
};

