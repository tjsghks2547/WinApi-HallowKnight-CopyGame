#pragma once
#include "CObject.h"

class CTexture;

class CHornetBossRoom : public CObject
{
private:
    CTexture* m_pTex;
 

public:
    virtual void update() override;
    virtual void render(HDC _dc) override;

public:
    CHornetBossRoom();
    ~CHornetBossRoom();
};

