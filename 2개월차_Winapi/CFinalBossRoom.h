#pragma once
#include "CObject.h"
class CFinalBossRoom :
    public CObject
{
    CTexture* m_pTex;
 


public:
    virtual void update() override;
    virtual void render(HDC _dc) override;

public:
    CFinalBossRoom();
    ~CFinalBossRoom();
};

